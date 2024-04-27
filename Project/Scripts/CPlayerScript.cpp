#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CKeyMgr.h>

#include "CPlayerHitCollider.h"
#include "CItem.h"
#include "CWhip.h"
#include "CParticleOnce.h"

CPlayerScript::CPlayerScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, InputKey()
	, m_fInvincibility(1.f)
	, m_vSocketPos(25.f, -22.f, 0.f)
	, m_UpForce(6.f, 8.f)
	, m_FrontForce(6.f, 5.f)
	, m_DownForce(6.f, -2.f)
{
	SetSpeed(900.f);
	SetHealth(50);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::HandOn(CGameObject* item)
{
	m_HandleItem = item->GetScript<CItem>();
	m_HandleItem->SetPlayerScript(this);
}

void CPlayerScript::PutDown()
{
	if (!m_HandleItem) return;

	m_HandleItem->PutDown();
	m_HandleItem = nullptr;
}

#include "CBomb.h"
void CPlayerScript::Bomb()
{
	if (GetBombCnt() <= 0) return;

	m_iBombCnt--;
	auto prefab = CAssetMgr::GetInst()->Load<CPrefab>(BombPrefKey, BombPrefKey);
	auto obj = prefab->Instantiate();
	auto bomb = obj->GetScript<CBomb>();

	Vec3 vPos = Transform()->GetRelativePos();
	if (IsLookRight()) {
		vPos.x += m_vSocketPos.x;
	}
	else {
		vPos.x -= m_vSocketPos.x;
	}

	vPos.y += m_vSocketPos.y;
	obj->Transform()->SetRelativePos(vPos);

	GamePlayStatic::SpawnGameObject(obj, ItemLayer);
	if (StateMachine()->GetFSM()->GetCurState()->GetStateType() == (UINT)STATE_TYPE::PLAYERDOWNSTATE) {
		obj->GetScript<CItem>()->SetPlayerScript(this);
		obj->GetScript<CItem>()->PutDown();
	}

	Vec2 force;
	if (KEY_PRESSED(InputKey.LookUp)) {
		force = m_UpForce;
	}
	else if (KEY_PRESSED(InputKey.LookDown)) {
		force = m_DownForce;

	}
	else {
		force = m_FrontForce;
	}
	if (!IsLookRight())
		force.x = -force.x;

	//force += GetVelocity();
	bomb->skill(force);

}

void CPlayerScript::Hit(int _damage)
{
	CCharacterScript::Hit(_damage);

	m_HitCollider->Collider2D()->Activate(false);

	m_fInvincibilityTimer = m_fInvincibility;
}

void CPlayerScript::Skill()
{
	Vec2 force;
	if (KEY_PRESSED(InputKey.LookUp)) {
		force = m_UpForce;
	}
	else if (KEY_PRESSED(InputKey.LookDown)) {
		force = m_DownForce;
	}
	else {
		force = m_FrontForce;
	}
	if (!IsLookRight())
		force.x = -force.x;

	//force += GetVelocity();
	m_HandleItem->skill(force);
	m_HandleItem->OutPlayerScript();
	m_HandleItem = nullptr;

	Animator2D()->Play(AnimPlayerThrow, false);
}

void CPlayerScript::Attack()
{
	m_Whip->Attack();
}

void CPlayerScript::CloudSpawn()
{
	CGameObject* obj = CParticleOnce::Instantiate(ParticleCloudPrefKey, TexParticleSmallAtlas);
	obj->Transform()->SetRelativePos(Vec3(GetOwner()->Transform()->GetRelativePos().x, GetOwner()->Transform()->GetRelativePos().y -GetOwner()->Transform()->GetRelativeScale().y / 2.f, -1));
	GamePlayStatic::SpawnGameObject(obj, PlayerLayer);
}

#include "CPlayerStartState.h"

bool CPlayerScript::IsMoving()
{	
	return KEY_NONE(InputKey.MoveLeft) && KEY_NONE(InputKey.MoveRight) ? false : true;
}
bool CPlayerScript::IsHandling()
{
	return m_HandleItem ? true : false;
}
Vec3 CPlayerScript::GetItemSocketPos()
{
	Vec3 pos = m_vSocketPos;
	if (!IsLookRight()) {
		pos.x = -m_vSocketPos.x;
	}
	return pos + Transform()->GetRelativePos(); 
}
bool CPlayerScript::DetectLadder()
{
	return m_iLadderCnt >0;
}
void CPlayerScript::begin()
{
	CCharacterScript::begin();

	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CPlayerStartState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));

	AddScriptParam(SCRIPT_PARAM::INT, "MoveFront", &m_bMoveFront);


	Vec2 ColliderCenterPos = Collider2D()->GetRelativePos();
	Vec2 ColliderScale = Collider2D()->GetRelativeScale();

	float ownerZ = Transform()->GetRelativePos().z;

	CGameObject* obj;

	m_HitCollider = new CPlayerHitCollider;
	obj = new CGameObject;
	obj->AddComponent(m_HitCollider);
	m_HitCollider->Set(GetOwner(), Vec3(Collider2D()->GetRelativePos().x, Collider2D()->GetRelativePos().y, ownerZ)
		, Vec3(Collider2D()->GetRelativeScale().x, Collider2D()->GetRelativeScale().y, 1));
	GetOwner()->AddChild(obj);
	GamePlayStatic::SpawnGameObject(obj, PlayerHitLayer);

	StateMachine()->AddBlackboardData(BBJumpDelay, BB_DATA::FLOAT, &m_fJumpDelayTimer);

	auto prefab = CAssetMgr::GetInst()->Load<CPrefab>(WhipPrefKey, WhipPrefKey);
	obj = prefab->Instantiate();
	obj->Transform()->SetRelativePos(Vec3(0, 0, -1));
	GetOwner()->AddChild(obj);
	m_Whip = obj->GetScript<CWhip>();
	GamePlayStatic::SpawnGameObject(obj, PlayerAttackLayer);

	m_iBombCnt = 4;
	m_iRopeCnt = 4;
}

void CPlayerScript::tick()
{
	CCharacterScript::tick();

	if (KEY_NONE(GetInputKeys().MoveLeft) && KEY_NONE(GetInputKeys().MoveRight)) {
		m_MovePriority = MovePriority::None;
	}

	if (KEY_TAP(GetInputKeys().MoveLeft)) {
		m_MovePriority = MovePriority::Left;
	}
	if (KEY_TAP(GetInputKeys().MoveRight)) {
		m_MovePriority = MovePriority::Right;
	}

	if (KEY_RELEASED(GetInputKeys().MoveLeft) && KEY_PRESSED(GetInputKeys().MoveRight)) {
		m_MovePriority = MovePriority::Right;
	}
	if (KEY_RELEASED(GetInputKeys().MoveRight) && KEY_PRESSED(GetInputKeys().MoveLeft)) {
		m_MovePriority = MovePriority::Left;
	}

	*(float*)StateMachine()->GetBlackboardData(BBJumpDelay) -= DT;

	if (!m_HitCollider->Collider2D()->IsActivate()) {
		m_fInvincibilityTimer -= DT;
		auto collider = GetOwner()->Collider2D();
		if (collider->IsActivate()) {
			collider->Activate(false);
		}
		else {
			collider->Activate(true);
		}

		if (m_fInvincibilityTimer < 0) {
			m_HitCollider->Collider2D()->Activate(true);
			collider->Activate(true);
		}
	}
}

#include "CTile.h"
#include "CMonsterHitCollider.h"

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {
		TileType type = tile->GetTileType();
		if (type == TileType::Ladder || type == TileType::LadderHalf) {
			m_iLadderCnt++;
			m_vRecentLadderPos = _OtherObj->Transform()->GetRelativePos();
		}
	}
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::Overlap(_Collider, _OtherObj, _OtherCollider);

	if (_OtherObj->GetScript<CItem>()) {
		auto state = StateMachine()->GetFSM()->GetCurState();
		if (state->GetStateType() == (UINT)STATE_TYPE::PLAYERDOWNSTATE) {
			if (KEY_TAP(InputKey.Attack)) {
				if (!IsHandling()) {
					HandOn(_OtherObj);
				}
				else {
					PutDown();
				}
			}
		}
	}
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);

	auto tile = _OtherObj->GetScript<CTile>();

	if (tile) {
		TileType type = tile->GetTileType();
		if (type == TileType::Ladder || type == TileType::LadderHalf) {
			m_iLadderCnt--;
		}
	}
}
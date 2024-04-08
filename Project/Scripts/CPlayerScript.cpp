#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CKeyMgr.h>

#include "CPlayerHitCollider.h"
#include "CItem.h"

CPlayerScript::CPlayerScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, InputKey()
	, m_fInvincibility(1.f)
	, m_vSocketPos(25.f, -22.f, 0.f)
{
	SetSpeed(6.f);
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

void CPlayerScript::Hit(int _damage)
{
	CCharacterScript::Hit(_damage);

	m_HitCollider->Collider2D()->Activate(false);

	m_fInvincibilityTimer = m_fInvincibility;
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

	m_ButtomCollider->SetName("PlayerGroundCollider");

	StateMachine()->AddBlackboardData(BBJumpDelay, BB_DATA::FLOAT, &m_fJumpDelayTimer);

}

void CPlayerScript::tick()
{
	CCharacterScript::tick();
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
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::Overlap(_Collider, _OtherObj, _OtherCollider);

	if (_OtherObj->GetScript<CItem>()) {
		auto state = StateMachine()->GetFSM()->GetCurState();
		if (state->GetStateType() == (UINT)STATE_TYPE::PLAYERDOWNSTATE) {
			if (KEY_TAP(InputKey.Attack)) {
				HandOn(_OtherObj);
			}
		}
	}
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
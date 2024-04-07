#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CKeyMgr.h>

#include "CPlayerHitCollider.h"

CPlayerScript::CPlayerScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, InputKey()
	, m_fJumpInitSpeed(6.7f)
	, m_fJumpTimer(0.f)
	, m_fJumpMaxTime(.3f)
	, m_fJumpWeightSpeed(1.5f)
	, m_fInvincibility(1.f)
	, m_fJumpDelay(0.5f)
{
	SetSpeed(6.f);
	SetHealth(50);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::Hit(int _damage)
{
	CCharacterScript::Hit(_damage);

	m_HitCollider->Collider2D()->Activate(false);

	m_fInvincibilityTimer = m_fInvincibility;
}

void CPlayerScript::Jump()
{
	if (m_fJumpDelayTimer > 0) {
		return;
	}

	if (IsGrounded()) {
		m_fJumpDelayTimer = m_fJumpDelay;
		SetVelocity(Vec2(0.f, m_fJumpInitSpeed));
		m_fJumpTimer = m_fJumpMaxTime;
		m_bJumpup = true;
		GetOwner()->Animator2D()->Play(AnimPlayerJumpUp, false);
		SetGround(false);
	}
	if (m_fJumpTimer > 0) {
		AddVelocity(Vec2(0.f, m_fJumpWeightSpeed * DT));
	}
}

void CPlayerScript::skill()
{
}

#include "CPlayerStartState.h"
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
}

void CPlayerScript::tick()
{
	CCharacterScript::tick();

	// Jump
	if (m_bJumpup) {
		if (m_fJumpTimer > 0) {
			m_fJumpTimer -= DT;
		}
		else {
			m_bJumpup = false;
			m_fJumpTimer = 0;
		}
	}
	else {
		if (IsGrounded()) {
			if (KEY_NONE(InputKey.MoveLeft) && KEY_NONE(InputKey.MoveRight)) {
				Animator2D()->Play(AnimPlayerIdle);
			}
			else {
			}
		}
	}
	m_fJumpDelayTimer -= DT;

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
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
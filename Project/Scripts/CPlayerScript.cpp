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
	if (IsGrounded()) {
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

	AddScriptParam(SCRIPT_PARAM::FLOAT, "JumpTimer", &m_fJumpTimer);
	AddScriptParam(SCRIPT_PARAM::INT, "Is ground", &m_bGround);
	AddScriptParam(SCRIPT_PARAM::INT, "Is left", &m_bLeftBump);
	AddScriptParam(SCRIPT_PARAM::INT, "Is right", &m_bRightBump);
	AddScriptParam(SCRIPT_PARAM::INT, "Health", &m_tInfo.Health);


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
			if (!IsMoving()) {
				Animator2D()->Play(AnimPlayerIdle);
			}
			else {
				//Animator2D()->Play(AnimPlayerIdle);
			}
		}
	}

	if (KEY_TAP(InputKey.MoveLeft)) {
		TurnLeft();
		if(IsGrounded())
			Animator2D()->Play(AnimPlayerWalk);
	}
	if (KEY_TAP(InputKey.MoveRight)) {
		TurnRight();
		if (IsGrounded())
			Animator2D()->Play(AnimPlayerWalk);
	}
	if (KEY_RELEASED(InputKey.MoveLeft)) {
		m_bTurnLeft = false;
	}
	if (KEY_RELEASED(InputKey.MoveRight)) {
		m_bTurnRight = false;
	}

	m_vPrevPos = m_vCurPos;
	m_vCurPos = GetOwner()->Transform()->GetRelativePos();

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
	auto script = _OtherObj->GetScript<CTile>();
	if (script)
	{
		if (!IsJumpUp()) {
			if (IsMoving()) {
				Animator2D()->Play(AnimPlayerWalk);
			}
			else {
				Animator2D()->Play(AnimPlayerIdle);
			}
		}
	}
	if (_OtherObj->GetScript<CMonsterHitCollider>())
	{
		SetGround(true);
		Jump();
	}
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
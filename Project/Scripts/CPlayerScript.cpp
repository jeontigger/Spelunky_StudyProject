#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CKeyMgr.h>

CPlayerScript::CPlayerScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, InputKey()
	, m_fJumpInitSpeed(6.7f)
	, m_fJumpTimer(0.f)
	, m_fJumpMaxTime(.3f)
	, m_fJumpWeightSpeed(1.5f)
{
	
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::Jump()
{
	if (IsGrounded()) {
		//auto pos = Transform()->GetRelativePos();
		//pos.y += 1.f;
		//Transform()->SetRelativePos(pos);
		SetVelocity(Vec2(0.f, m_fJumpInitSpeed));
		m_fJumpTimer = m_fJumpMaxTime;
		m_bJumpup = true;
		GetOwner()->Animator2D()->Play(AnimPlayerJumpUp, false);
		m_bGround = 0;
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
	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CPlayerStartState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));

	AddScriptParam(SCRIPT_PARAM::FLOAT, "JumpTimer", &m_fJumpTimer);
	AddScriptParam(SCRIPT_PARAM::INT, "Is ground", &m_bGround);
	AddScriptParam(SCRIPT_PARAM::INT, "Is left", &m_bLeftBump);
	AddScriptParam(SCRIPT_PARAM::INT, "Is right", &m_bRightBump);
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
		MoveLeft();
		if(IsGrounded())
			Animator2D()->Play(AnimPlayerWalk);
	}
	if (KEY_TAP(InputKey.MoveRight)) {
		MoveRight();
		if (IsGrounded())
			Animator2D()->Play(AnimPlayerWalk);
	}
	if (KEY_RELEASED(InputKey.MoveLeft)) {
		m_bMoveLeft = false;
	}
	if (KEY_RELEASED(InputKey.MoveRight)) {
		m_bMoveRight = false;
	}

	m_vPrevPos = m_vCurPos;
	m_vCurPos = GetOwner()->Transform()->GetRelativePos();
}

#include "CTile.h"

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
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::EndOverlap(_Collider, _OtherObj, _OtherCollider);
}
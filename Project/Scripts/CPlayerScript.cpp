#include "pch.h"
#include "CPlayerScript.h"

#include <Engine/CKeyMgr.h>

CPlayerScript::CPlayerScript()
	: CFieldObject((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, InputKey()
	, m_fJumpInitSpeed(0.7f)
	, m_fJumpTimer(0.f)
	, m_fJumpMaxTime(.3f)
	, m_fJumpWeightSpeed(1.5f)
	, m_fRunSpeed(1.f)
{
	
}

CPlayerScript::~CPlayerScript()
{

}

bool CPlayerScript::IsLookRight()
{
	return m_bMoveRight;
}

void CPlayerScript::MoveLeft()
{
	m_bMoveLeft = true;
}

void CPlayerScript::MoveRight()
{
	m_bMoveRight = true;
}

void CPlayerScript::Jump()
{
	if (IsGrounded()) {
		auto pos = Transform()->GetRelativePos();
		pos.y += 1.f;
		Transform()->SetRelativePos(pos);
		SetVelocity(Vec2(0.f, m_fJumpInitSpeed));
		m_fJumpTimer = m_fJumpMaxTime;
		m_bJumpup = true;
		GetOwner()->Animator2D()->Play(AnimPlayerJumpUp, false);
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
}

void CPlayerScript::tick()
{
	CFieldObject::tick();
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

	// Move
	Vec2 vel = GetVelocity();
	if (m_bMoveRight && m_bMoveLeft) {
		m_bLastMoveDir ? m_bMoveLeft = false: m_bMoveRight = false;
	}

	if (m_bMoveRight) {
		vel.x = m_fRunSpeed;
		Vec3 scale = Transform()->GetRelativeScale();
		scale.x = abs(scale.x);
		Transform()->SetRelativeScale(scale);
	}

	if (m_bMoveLeft) {
		vel.x = -m_fRunSpeed;
		Vec3 scale = Transform()->GetRelativeScale();
		scale.x = -(abs(scale.x));
		Transform()->SetRelativeScale(scale);
	}

	if (!m_bMoveLeft && !m_bMoveRight) {
		vel.x = 0;
	}

	SetVelocity(vel);
	if (KEY_TAP(InputKey.MoveLeft)) {
		m_bLastMoveDir = 0;
		m_bMoveLeft = true;
		if (IsRightBump()) {
			SetRightBump(false);
		}
		if(IsGrounded())
			Animator2D()->Play(AnimPlayerWalk);
	}
	if (KEY_TAP(InputKey.MoveRight)) {
		m_bLastMoveDir = 1;
		m_bMoveRight = true;
		if (IsLeftBump()) {
			SetLeftBump(false);
		}
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
	CFieldObject::BeginOverlap(_Collider, _OtherObj, _OtherCollider);
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
	CFieldObject::Overlap(_Collider, _OtherObj, _OtherCollider);
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObject::EndOverlap(_Collider, _OtherObj, _OtherCollider);
	/*auto script = _OtherObj->GetScript<CTile>();
	if (script)
		SetGround(false);*/
}
#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: CFieldObject((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_fJumpInitSpeed(0.7f)
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
		SetGround(false);
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
}

void CPlayerScript::tick()
{
	CFieldObject::tick();

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
			Animator2D()->Play(AnimPlayerIdle);
		}
	}


	

}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
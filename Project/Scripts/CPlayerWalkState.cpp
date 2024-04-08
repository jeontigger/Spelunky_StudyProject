#include "pch.h"
#include "CPlayerWalkState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerWalkState::CPlayerWalkState()
	: CState((UINT)STATE_TYPE::PLAYERWALKSTATE)
{
}

CPlayerWalkState::~CPlayerWalkState()
{
}

void CPlayerWalkState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
}

void CPlayerWalkState::finaltick()
{

	if (KEY_PRESSED(m_Script->GetInputKeys().Jump)) {
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0.f) {
			if(m_Script->IsGrounded())
				ChangeState(StatePlayerJumpUp);
		}
	}

	// 공격
	if (KEY_TAP(m_Script->GetInputKeys().Attack)) {
		// 채찍
		if (!m_Script->IsHandling()) {
			ChangeState(StatePlayerAttack);
		}
		// 던지기
		else {
			m_Script->Skill();
		}
	}

	
	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		m_Script->TurnLeft();
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		m_Script->TurnRight();
	}

	if (KEY_RELEASED(m_Script->GetInputKeys().MoveLeft)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveRight)) {
			m_Script->TurnRight();
		}
	}
	if (KEY_RELEASED(m_Script->GetInputKeys().MoveRight)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveLeft)) {
			m_Script->TurnLeft();
		}
	}

	if (m_Script->IsMoving()) {
		m_Script->MoveFront();
	}
	else {
		ChangeState(StatePlayerIdle);
	}

	if (KEY_PRESSED(m_Script->GetInputKeys().LookDown)) {
		ChangeState(StatePlayerDown);
	}

}

void CPlayerWalkState::Exit()
{
	m_Script->Stop();
}

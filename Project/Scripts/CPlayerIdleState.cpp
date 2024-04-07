#include "pch.h"
#include "CPlayerIdleState.h"

#include <Engine/CKeyMgr.h>

#include "CPlayerScript.h"

CPlayerIdleState::CPlayerIdleState()
	: CState((UINT)STATE_TYPE::PLAYERIDLESTATE)
{
	
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::finaltick()
{
	PlayerKey input = m_PlayerScript->GetInputKeys();

	
	if (KEY_PRESSED(input.Jump)) { 
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0.f) {
			if (m_PlayerScript->IsGrounded())
			ChangeState(StatePlayerJumpUp);
		}
	}

	if (KEY_TAP(m_PlayerScript->GetInputKeys().MoveLeft)) {
		m_PlayerScript->TurnLeft();
	}
	if (KEY_TAP(m_PlayerScript->GetInputKeys().MoveRight)) {
		m_PlayerScript->TurnRight();
	}

	if (m_PlayerScript->IsMoving()) {
		m_PlayerScript->MoveFront();
	}
	else {
		m_PlayerScript->Stop();
	}


	if (KEY_PRESSED(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}

}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

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
			ChangeState(StatePlayerJumpUp);
		}
	}

	if (KEY_TAP(input.MoveLeft)) {
		m_PlayerScript->TurnLeft();
		if (m_PlayerScript->IsGrounded())
			m_PlayerScript->Animator2D()->Play(AnimPlayerWalk);
	}
	if(KEY_TAP(input.MoveRight)) {
		m_PlayerScript->TurnRight();
		if(m_PlayerScript->IsGrounded())
			m_PlayerScript->Animator2D()->Play(AnimPlayerWalk);
	}

	if (KEY_PRESSED(input.MoveLeft)|| KEY_PRESSED(input.MoveRight)) {
		if (KEY_NONE(input.MoveLeft)) {
			m_PlayerScript->TurnRight();
		}
		else if (KEY_NONE(input.MoveRight)) {
			m_PlayerScript->TurnLeft();
		}
		m_PlayerScript->MoveFront();
	}

	if (KEY_NONE(input.MoveLeft) && KEY_NONE(input.MoveRight)) {
		m_PlayerScript->Stop();
	}

	if (KEY_TAP(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}

	*(float*)GetBlackboardData(BBJumpDelay) -= DT;
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

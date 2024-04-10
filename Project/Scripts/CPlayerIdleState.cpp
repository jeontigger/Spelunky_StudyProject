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

	// 점프
	if (KEY_PRESSED(input.Jump)) { 
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0.f) {
			if (m_PlayerScript->IsGrounded())
			ChangeState(StatePlayerJumpUp);
		}
	}

	// 사다리 타기
	if (KEY_PRESSED(input.LookUp)) {
		if(m_PlayerScript->DetectLadder())
			ChangeState(StatePlayerLadder);
	}

	// 아래 보기
	if (KEY_PRESSED(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}
	
	// 공격
	if (KEY_TAP(input.Attack)) {
		// 채찍
		if (!m_PlayerScript->IsHandling()) {
			ChangeState(StatePlayerAttack);
		}
		// 던지기
		else {
			ChangeState(StatePlayerThrow);
		}
	}

	// 폭탄
	if (KEY_TAP(input.Bomb)) {
		m_PlayerScript->Bomb();
	}

	// 움직임
	if (KEY_TAP(m_PlayerScript->GetInputKeys().MoveLeft)) {
		m_PlayerScript->TurnLeft();
	}
	if (KEY_TAP(m_PlayerScript->GetInputKeys().MoveRight)) {
		m_PlayerScript->TurnRight();
	}

	if (KEY_RELEASED(m_PlayerScript->GetInputKeys().MoveLeft)) {
		if (KEY_PRESSED(m_PlayerScript->GetInputKeys().MoveRight)) {
			m_PlayerScript->TurnRight();
		}
	}
	if (KEY_RELEASED(m_PlayerScript->GetInputKeys().MoveRight)) {
		if (KEY_PRESSED(m_PlayerScript->GetInputKeys().MoveLeft)) {
			m_PlayerScript->TurnLeft();
		}
	}

	if (m_PlayerScript->IsMoving()) {
		m_PlayerScript->MoveFront();
		ChangeState(StatePlayerWalk);
	}
	else {
		m_PlayerScript->Stop();
	}

}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	if (m_PlayerScript->IsHandling()) {
		m_Player->Animator2D()->Play(AnimPlayerHandleIdle);
	}
	else {
		m_Player->Animator2D()->Play(AnimPlayerIdle);
	}
}

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

	// ����
	if (KEY_PRESSED(input.Jump)) { 
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0.f) {
			if (m_PlayerScript->IsGrounded())
			ChangeState(StatePlayerJumpUp);
		}
	}

	// ��ٸ� Ÿ��
	if (KEY_PRESSED(input.LookUp)) {
		if(m_PlayerScript->DetectLadder())
			ChangeState(StatePlayerLadder);
	}

	// �Ʒ� ����
	if (KEY_PRESSED(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}
	
	// ����
	if (KEY_TAP(input.Attack)) {
		// ä��
		if (!m_PlayerScript->IsHandling()) {
			ChangeState(StatePlayerAttack);
		}
		// ������
		else {
			ChangeState(StatePlayerThrow);
		}
	}

	// ��ź
	if (KEY_TAP(input.Bomb)) {
		m_PlayerScript->Bomb();
	}

	// ������
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

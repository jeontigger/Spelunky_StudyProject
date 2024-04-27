#include "pch.h"
#include "CPlayerIdleState.h"

#include <Engine/CKeyMgr.h>

#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerIdleState::CPlayerIdleState()
	: CState((UINT)STATE_TYPE::PLAYERIDLESTATE)
{
	
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::finaltick()
{
	PlayerKey input = m_Script->GetInputKeys();
	MovePriority priority = m_Script->GetMovePriority();

	// 좌우 움직임
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		ChangeState(StatePlayerWalkLeft);
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		ChangeState(StatePlayerWalkRight);
	}

	// 점프
	if (KEY_TAP(input.Jump)|| KEY_PRESSED(input.Jump)) {
		if(m_Script->CanJump())
			ChangeState(StatePlayerJumpUp);
	}

	// 낙하
	if (!m_Script->IsGrounded()) {
		ChangeState(StatePlayerFallDown);
	}

	// 수구리기
	if (KEY_TAP(input.LookDown) || KEY_PRESSED(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}

	m_Movement->SetVelocityX(0.f);
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerIdle);

	if (m_Script->IsHandling()) {
		m_Player->Animator2D()->Play(AnimPlayerHandleIdle);
	}
	else {
	}
}

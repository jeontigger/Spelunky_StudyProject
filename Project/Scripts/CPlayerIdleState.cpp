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

	if (KEY_PRESSED(input.MoveLeft)) {
		m_PlayerScript->TurnLeft();
		ChangeState(StatePlayerWalk);
	}
	if(KEY_PRESSED(input.MoveRight)) {
		m_PlayerScript->TurnRight();
		ChangeState(StatePlayerWalk);
	}


	if (KEY_TAP(input.LookDown)) {
		ChangeState(StatePlayerDown);
	}

}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

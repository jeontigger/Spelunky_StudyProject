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
			m_PlayerScript->Jump();
	}
	if (KEY_TAP(input.MoveLeft)) {
		m_PlayerScript->TurnLeft();
		if (!m_PlayerScript->IsJumpUp())
			m_PlayerScript->Animator2D()->Play(AnimPlayerWalk);
	}
	if(KEY_TAP(input.MoveRight)) {
		m_PlayerScript->TurnRight();
		if(!m_PlayerScript->IsJumpUp())
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
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

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
	if (KEY_PRESSED(input.MoveLeft)) {
		m_PlayerScript->TurnLeft();
		m_PlayerScript->MoveFront();
	}
	if (KEY_PRESSED(input.MoveRight)) {
		m_PlayerScript->TurnRight();
		m_PlayerScript->MoveFront();
	}
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

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
		m_PlayerScript->MoveLeft();
	}
	if (KEY_PRESSED(input.MoveRight)) {
		m_PlayerScript->MoveRight();
	}
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

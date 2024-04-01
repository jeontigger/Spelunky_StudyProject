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
	if (KEY_PRESSED(SPACE)) { 
			m_PlayerScript->Jump();
	}
	if (KEY_PRESSED(LEFT)) {
		m_PlayerScript->MoveLeft();
	}
	if (KEY_PRESSED(RIGHT)) {
		m_PlayerScript->MoveRight();
	}
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerIdle);
}

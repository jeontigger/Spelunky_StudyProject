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
	PlayerKey input = m_PlayerScript->GetInputKeys();

	if (KEY_TAP(input.MoveLeft)) {
		ChangeState(StatePlayerWalkLeft);
	}

	if (KEY_TAP(input.MoveRight)) {
		ChangeState(StatePlayerWalkRight);
	}

	m_Movement->SetVelocityX(0.f);
}

void CPlayerIdleState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_PlayerScript = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerIdle);

	if (m_PlayerScript->IsHandling()) {
		m_Player->Animator2D()->Play(AnimPlayerHandleIdle);
	}
	else {
	}
}

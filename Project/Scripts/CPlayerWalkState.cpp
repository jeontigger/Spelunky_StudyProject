#include "pch.h"
#include "CPlayerWalkState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerWalkState::CPlayerWalkState()
	: CState((UINT)STATE_TYPE::PLAYERWALKSTATE)
{
}

CPlayerWalkState::~CPlayerWalkState()
{
}

void CPlayerWalkState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
}

void CPlayerWalkState::finaltick()
{
	if (m_Script->IsMoving()) {
		m_Script->MoveFront();
	}
	else {
		ChangeState(StatePlayerIdle);
	}

	if (KEY_TAP(m_Script->GetInputKeys().Jump)) {
		ChangeState(StatePlayerJumpUp);
	}

	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		m_Script->TurnLeft();
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		m_Script->TurnRight();
	}

}

void CPlayerWalkState::Exit()
{
	m_Script->Stop();
}

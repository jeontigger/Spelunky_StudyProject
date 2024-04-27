#include "pch.h"
#include "CPlayerWalkState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

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
	if (KEY_RELEASED(LEFT)) {
		ChangeState(StatePlayerIdle);
	}

	m_Player->GetScript<CMovement>()->SetVelocityX(m_Script->GetSpeed());
}

void CPlayerWalkState::Exit()
{
	//m_Script->Stop();
}

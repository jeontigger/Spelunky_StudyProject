#include "pch.h"
#include "CPlayerThrowState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerThrowState::CPlayerThrowState()
	: CState((UINT)STATE_TYPE::PLAYERTHROWSTATE)
{
}

CPlayerThrowState::~CPlayerThrowState()
{
}

void CPlayerThrowState::finaltick()
{
	if (m_Player->Animator2D()->GetCurAnim()->IsFinish()) {
		if (!m_Script->IsGrounded()) {
			ChangeState(StatePlayerFallDown);
		}
		if (m_Script->IsMoving()) {
			ChangeState(StatePlayerWalk);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
	}

	PlayerMoveDefault;
}

void CPlayerThrowState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Player->Animator2D()->Play(AnimPlayerThrow);
	m_Script = m_Player->GetScript<CPlayerScript>();

	m_Script->Skill();
}

void CPlayerThrowState::Exit()
{
}

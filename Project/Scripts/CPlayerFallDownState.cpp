#include "pch.h"
#include "CPlayerFallDownState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
void CPlayerFallDownState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerJumpFall);
}

void CPlayerFallDownState::finaltick()
{
	if (m_Script->IsGrounded()) {
		ChangeState(StatePlayerIdle);
	}

	// 공격
	if (KEY_TAP(m_Script->GetInputKeys().Attack)) {
		// 채찍
		if (!m_Script->IsHandling()) {
			ChangeState(StatePlayerAttack);
		}
		// 던지기
		else {
			ChangeState(StatePlayerThrow);
		}
	}


	PlayerMoveDefault;
}

void CPlayerFallDownState::Exit()
{
}

CPlayerFallDownState::CPlayerFallDownState()
	:CState((UINT)STATE_TYPE::PLAYERFALLDOWNSTATE)
{
}

CPlayerFallDownState::~CPlayerFallDownState()
{
}

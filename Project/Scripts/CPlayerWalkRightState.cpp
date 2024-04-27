#include "pch.h"
#include "CPlayerWalkRightState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerWalkRightState::CPlayerWalkRightState()
	: CState((UINT)STATE_TYPE::PLAYERWALKLEFTSTATE)
{
}

CPlayerWalkRightState::~CPlayerWalkRightState()
{
}

void CPlayerWalkRightState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
	m_Script->TurnRight();
}

void CPlayerWalkRightState::finaltick()
{
	auto input = m_Script->GetInputKeys();

	if (KEY_RELEASED(input.MoveRight)) {
		if (KEY_PRESSED(input.MoveLeft)) {
			ChangeState(StatePlayerWalkLeft);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
	}

	if (KEY_TAP(input.MoveLeft)) {
		ChangeState(StatePlayerWalkLeft);
	}

	// ³«ÇÏ
	if (!m_Script->IsGrounded()) {
		ChangeState(StatePlayerFallDown);
	}

	// Á¡ÇÁ
	if (KEY_TAP(input.Jump) || KEY_PRESSED(input.Jump)) {
		if (m_Script->CanJump())
			ChangeState(StatePlayerJumpUp);
	}

	m_Movement->SetVelocityX(m_Script->GetSpeed());
}

void CPlayerWalkRightState::Exit()
{
}

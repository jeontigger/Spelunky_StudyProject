#include "pch.h"
#include "CPlayerFallDownState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

void CPlayerFallDownState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();
	m_Player->Animator2D()->Play(AnimPlayerJumpFall);
}

void CPlayerFallDownState::finaltick()
{
	m_Movement->SetVelocityX(0);
	auto input = m_Script->GetInputKeys();
	MovePriority priority = m_Script->GetMovePriority();

	if (m_Script->IsGrounded()) {
		if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
			ChangeState(StatePlayerWalkLeft);
		}
		else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
			ChangeState(StatePlayerWalkRight);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
		m_Script->CloudSpawn();
	}

	// ÁÂ¿ì ¿òÁ÷ÀÓ
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		m_Script->TurnLeft();
		m_Movement->SetVelocityX(-m_Script->GetSpeed());
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		m_Script->TurnRight();
		m_Movement->SetVelocityX(m_Script->GetSpeed());
	}

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

#include "pch.h"
#include "CPlayerWalkLeftState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerWalkLeftState::CPlayerWalkLeftState()
	: CState((UINT)STATE_TYPE::PLAYERWALKLEFTSTATE)
{
}

CPlayerWalkLeftState::~CPlayerWalkLeftState()
{
}

void CPlayerWalkLeftState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
	m_Script->TurnLeft();
}

void CPlayerWalkLeftState::finaltick()
{
	auto input = m_Script->GetInputKeys();

	if (KEY_RELEASED(input.MoveLeft)) {
		if (KEY_PRESSED(input.MoveRight)) {
			ChangeState(StatePlayerWalkRight);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
	}

	if (KEY_TAP(input.MoveRight)) {
		ChangeState(StatePlayerWalkRight);
	}

	// 낙하
	if (!m_Script->IsGrounded()) {
		ChangeState(StatePlayerFallDown);
	}

	// 점프
	if (KEY_TAP(input.Jump) || KEY_PRESSED(input.Jump)) {
		if (m_Script->CanJump())
			ChangeState(StatePlayerJumpUp);
	}

	// 공격
	if (KEY_TAP(input.Attack)) {
		ChangeState(StatePlayerAttack);
	}

	m_Player->GetScript<CMovement>()->SetVelocityX(-m_Script->GetSpeed());
}

void CPlayerWalkLeftState::Exit()
{
	//m_Script->Stop();
}

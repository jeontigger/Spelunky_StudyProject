#include "pch.h"
#include "CPlayerAttackState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerAttackState::CPlayerAttackState()
	: CState((UINT)STATE_TYPE::PLAYERATTACKSTATE)
	, m_Player(nullptr)
	, m_Script(nullptr)
	, m_Movement(nullptr)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::finaltick()
{
	auto priority = m_Script->GetMovePriority();
	auto input = m_Script->GetInputKeys();

	CAnim* anim = m_Player->Animator2D()->GetCurAnim();
	m_Movement->SetVelocityX(0);

	if (anim->IsFinish())
	{
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
		}
		else {
			ChangeState(StatePlayerFallDown);
		}
	}

	// ÁÂ¿ì ¿òÁ÷ÀÓ
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		m_Movement->SetVelocityX(-m_Script->GetSpeed());
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		m_Movement->SetVelocityX(m_Script->GetSpeed());
	}
}

void CPlayerAttackState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Script->Attack();
	m_Player->Animator2D()->Play(AnimPlayerAttack);
}

void CPlayerAttackState::Exit()
{
}

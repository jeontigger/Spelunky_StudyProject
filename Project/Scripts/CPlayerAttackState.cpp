#include "pch.h"
#include "CPlayerAttackState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CWhip.h"

CPlayerAttackState::CPlayerAttackState()
	: CState((UINT)STATE_TYPE::PLAYERATTACKSTATE)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::finaltick()
{
	CAnim* anim = m_Player->Animator2D()->GetCurAnim();
	if (anim->IsFinish())
	{
		if (m_Script->IsGrounded()) {
			if (m_Script->IsMoving()) {
				ChangeState(StatePlayerWalk);
			}
			else {
				ChangeState(StatePlayerIdle);
			}
		}
		else {
			ChangeState(StatePlayerFallDown);
		}
	}

	PlayerMoveDefault;
	
}

void CPlayerAttackState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Script->Attack();
	m_Whip = m_Script->GetWhip();
	m_Player->Animator2D()->Play(AnimPlayerAttack);
}

void CPlayerAttackState::Exit()
{
}

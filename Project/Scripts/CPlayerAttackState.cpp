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
	CAnim* anim = m_Whip->Animator2D()->GetCurAnim();
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

	int idx = anim->GetIdx();
	int positive = 1.f;
	if (m_Script->IsLookRight()) {
		positive = 1.f;
	}
	else {
		positive = -1.f;
	}

	if (idx == 0) {
		m_Whip->Transform()->SetRelativePos(Vec3(-60, 48, positive * WhipBackZ));
		m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.8f));
	}
	else if (idx == 1) {
		m_Whip->Transform()->SetRelativePos(Vec3(-60, 28, positive*WhipBackZ));
		m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 2) {
		m_Whip->Transform()->SetRelativePos(Vec3(-60, 28, positive * WhipBackZ));
		m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.8f));
	}
	else if (idx == 3) {
		m_Whip->Transform()->SetRelativePos(Vec3(0, 20, positive * WhipBackZ));
		m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.8f));
	}
	else if (idx == 4) {
		m_Whip->Transform()->SetRelativePos(Vec3(75, -25, positive* WhipBackZ));
		m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.2f));
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
	m_Whip->Transform()->SetRelativePos(Vec3(-60, 48, WhipBackZ));
	m_Whip->Collider2D()->SetOffsetScale(Vec2(0.8f, 0.8f));
}

void CPlayerAttackState::Exit()
{
}

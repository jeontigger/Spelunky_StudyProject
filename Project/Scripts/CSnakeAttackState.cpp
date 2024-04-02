#include "pch.h"
#include "CSnakeAttackState.h"

#include <Engine\CAnimator2D.h>
#include <Engine\CTimeMgr.h>

#include "CSnakeScript.h"
#include "CSnakeIdleState.h"

CSnakeAttackState::CSnakeAttackState()
	: CState((UINT)STATE_TYPE::SNAKEATTACKSTATE)
{
}

CSnakeAttackState::~CSnakeAttackState()
{
}

void CSnakeAttackState::finaltick()
{
	if (m_fDuration < 0) {
		auto state = GetFSM()->GetState<CSnakeIdleState>();
		ChangeState(CStateMgr::GetStateName(state));
	}

	m_fDuration -= DT;
}
void CSnakeAttackState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);


	m_pOwner->Animator2D()->Play(AnimSnakeAttack, false);
	auto anim = m_pOwner->Animator2D()->GetCurAnim();
	m_fDuration = CAnimator2D::GetAnimDuration(anim);
}

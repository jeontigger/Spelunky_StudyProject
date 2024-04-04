#include "pch.h"
#include "CSnakeIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CTransform.h>

#include	"CSnakeScript.h"
#include "CSnakeAttackState.h"

CSnakeIdleState::CSnakeIdleState()
	: CState((UINT)STATE_TYPE::SNAKEIDLESTATE)
	, m_pPlayer(nullptr)
{

}

CSnakeIdleState::~CSnakeIdleState()
{
}

void CSnakeIdleState::finaltick()
{
	if (m_pScript->DetectPlayer()) {
		auto state = GetFSM()->GetState<CSnakeAttackState>();
		ChangeState(CStateMgr::GetStateName(state));
	}

	Vec3 targetPos = m_pPlayer->Transform()->GetRelativePos();

	static bool GoRight = false;
	static bool prev = GoRight;
	if (m_pScript->IsGrounded() && (!m_pScript->DetectFrontTile()|| m_pScript->DetectFrontWall())) {
		if (prev == GoRight) {
			if (m_pScript->IsLookRight()) {
				GoRight = false;
			}
			else {
				GoRight = true;
			}
		}
		else {
			prev = GoRight;
		}
	}

	if (GoRight) {
		m_pScript->TurnRight();
	}
	else {
		m_pScript->TurnLeft();
	}
	m_pScript->MoveFront();
	
}

void CSnakeIdleState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pOwner->Animator2D()->Play(AnimSnakeWalk);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);
}

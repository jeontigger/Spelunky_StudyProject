#include "pch.h"
#include "CSnakeIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CTransform.h>

#include	"CSnakeScript.h"

CSnakeIdleState::CSnakeIdleState()
	: CState((UINT)STATE_TYPE::SNAKEIDLESTATE)
	, m_fAttackRange(20.f)
	, m_pPlayer(nullptr)
{

}

CSnakeIdleState::~CSnakeIdleState()
{
}

void CSnakeIdleState::finaltick()
{
	Vec3 targetPos = m_pPlayer->Transform()->GetRelativePos();

	static bool GoRight = false;
	static bool prev = GoRight;
	if (m_pScript->IsGrounded() && !m_pScript->DetectFrontTile()) {
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
		m_pScript->SetLeftBump(false);
		m_pScript->MoveRight();
	}
	else {
		m_pScript->SetRightBump(false);
		m_pScript->MoveLeft();
	}
	
}

void CSnakeIdleState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pOwner->Animator2D()->Play(AnimSnakeWalk);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);
}

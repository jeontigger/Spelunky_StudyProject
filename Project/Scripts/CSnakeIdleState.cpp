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

	static bool turn = false;
	if (turn) {
		m_pScript->MoveRight();
	}
	else {
		m_pScript->MoveLeft();
	}
	
	
	if (m_pScript->IsGrounded() && !m_pScript->DetectFrontTile()) {
		int a = 0;
		turn = !turn;
	}
}

void CSnakeIdleState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pOwner->Animator2D()->Play(AnimSnakeWalk);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);
}

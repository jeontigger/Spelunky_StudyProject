#include "pch.h"
#include "CSnakeAttackState.h"

#include "CSnakeScript.h"
void CSnakeAttackState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);


	m_pOwner->Animator2D()->Play(AnimSnakeAttack, false);
}

CSnakeAttackState::CSnakeAttackState()
	: CState((UINT)STATE_TYPE::SNAKEATTACKSTATE)
{
}

CSnakeAttackState::~CSnakeAttackState()
{
}

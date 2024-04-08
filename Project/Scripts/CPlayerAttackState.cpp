#include "pch.h"
#include "CPlayerAttackState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerAttackState::CPlayerAttackState()
	: CState((UINT)STATE_TYPE::PLAYERATTACKSTATE)
{
}

CPlayerAttackState::~CPlayerAttackState()
{
}

void CPlayerAttackState::finaltick()
{

}

void CPlayerAttackState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
}

void CPlayerAttackState::Exit()
{
}

#include "pch.h"
#include "CPlayerStartState.h"

#include <Engine/CStateMachine.h>
#include "CPlayerIdleState.h"

void CPlayerStartState::finaltick()
{
	auto state = GetFSM()->GetState<CPlayerIdleState>();
	ChangeState(CStateMgr::GetStateName(state));
}

void CPlayerStartState::Enter()
{
	GetFSM()->GetStateMachine()->AddBlackboardData(L"bbdatakey", BB_DATA::INT, &m_temp);
}

void CPlayerStartState::Exit()
{
}

CPlayerStartState::CPlayerStartState()
	: CState((UINT)STATE_TYPE::PLAYERSTARTSTATE)
	, m_temp(33)
{
} 

CPlayerStartState::~CPlayerStartState()
{
}

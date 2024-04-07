#include "pch.h"
#include "CPlayerStartState.h"

#include <Engine/CStateMachine.h>
#include "CPlayerIdleState.h"

void CPlayerStartState::finaltick()
{

}

void CPlayerStartState::Enter()
{
	auto obj = GetFSM()->GetStateMachine()->GetOwner();
	//GetFSM()->GetStateMachine()->AddBlackboardData(L"bbdatakey", BB_DATA::INT, &m_temp);
	GetFSM()->GetStateMachine()->AddBlackboardData(BBOwnerKey, BB_DATA::OBJECT, obj);
	auto state = GetFSM()->GetState<CPlayerIdleState>();
	ChangeState(CStateMgr::GetStateName(state));
}

void CPlayerStartState::Exit()
{
}

CPlayerStartState::CPlayerStartState()
	: CState((UINT)STATE_TYPE::PLAYERSTARTSTATE)
{
} 

CPlayerStartState::~CPlayerStartState()
{
}

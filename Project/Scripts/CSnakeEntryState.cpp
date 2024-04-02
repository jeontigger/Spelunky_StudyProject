#include "pch.h"
#include "CSnakeEntryState.h"

#include <Engine/CFSM.h>
#include <Engine/CStateMachine.h>


#include "CSnakeScript.h"
#include "CSnakeIdleState.h"

void CSnakeEntryState::Enter()
{
	auto obj = GetFSM()->GetStateMachine()->GetOwner();
	/*GetFSM()->GetStateMachine()->AddBlackboardData(L"", BB_DATA::INT, &m_temp);
	GetFSM()->GetStateMachine()->AddBlackboardData(BBOwnerKey, BB_DATA::OBJECT, obj);*/

	auto state = GetFSM()->GetState<CSnakeIdleState>();
	ChangeState(CStateMgr::GetStateName(state));
}

void CSnakeEntryState::Exit()
{
}

CSnakeEntryState::CSnakeEntryState()
	: CState((UINT)STATE_TYPE::SNAKEENTRYSTATE)
{
}

CSnakeEntryState::~CSnakeEntryState()
{
}

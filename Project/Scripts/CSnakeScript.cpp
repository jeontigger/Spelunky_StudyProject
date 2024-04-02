#include "pch.h"
#include "CSnakeScript.h"

#include "CSnakeEntryState.h"
CSnakeScript::CSnakeScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::SNAKESCRIPT)
{

}

CSnakeScript::~CSnakeScript()
{
}

void CSnakeScript::begin()
{
	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CSnakeEntryState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));
}
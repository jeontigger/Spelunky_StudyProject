#include "pch.h"
#include "CStateMgr.h"

#include "CPlayerIdleState.h"
#include "CPlayerDownState.h"
#include "CPlayerStartState.h"
#include "CSnakeEntryState.h"
#include "CSnakeIdleState.h"
#include "CSnakeAttackState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CPlayerIdleState");
	_vec.push_back(L"CPlayerDownState");
	_vec.push_back(L"CPlayerStartState");
	_vec.push_back(L"CSnakeEntryState");
	_vec.push_back(L"CSnakeIdleState");
	_vec.push_back(L"CSnakeAttackState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CPlayerIdleState" == _strStateName)
		return new CPlayerIdleState;
	if (L"CPlayerDownState" == _strStateName)
		return new CPlayerDownState;
	if (L"CPlayerStartState" == _strStateName)
		return new CPlayerStartState;
	if (L"CSnakeEntryState" == _strStateName)
		return new CSnakeEntryState;
	if (L"CSnakeIdleState" == _strStateName)
		return new CSnakeIdleState;
	if (L"CSnakeAttackState" == _strStateName)
		return new CSnakeAttackState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new CPlayerIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERDOWNSTATE:
		return new CPlayerDownState;
		break;
	case (UINT)STATE_TYPE::PLAYERSTARTSTATE:
		return new CPlayerStartState;
		break;
	case (UINT)STATE_TYPE::SNAKEENTRYSTATE:
		return new CSnakeEntryState;
		break;
	case (UINT)STATE_TYPE::SNAKEIDLESTATE:
		return new CSnakeIdleState;
		break;
	case (UINT)STATE_TYPE::SNAKEATTACKSTATE:
		return new CSnakeAttackState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::PLAYERIDLESTATE:
		return L"CPlayerIdleState";
		break;

	case STATE_TYPE::PLAYERDOWNSTATE:
		return L"CPlayerDownState";
		break;

	case STATE_TYPE::PLAYERSTARTSTATE:
		return L"CPlayerStartState";
		break;

	case STATE_TYPE::SNAKEENTRYSTATE:
		return L"CSnakeEntryState";
		break;

	case STATE_TYPE::SNAKEIDLESTATE:
		return L"CSnakeIdleState";
		break;

	case STATE_TYPE::SNAKEATTACKSTATE:
		return L"CSnakeAttackState";
		break;

	}
	return nullptr;
}
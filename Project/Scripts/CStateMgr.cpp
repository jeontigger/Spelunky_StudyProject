#include "pch.h"
#include "CStateMgr.h"

#include "CPlayerIdleState.h"
#include "CPlayerWalkState.h"
#include "CPlayerStartState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CPlayerIdleState");
	_vec.push_back(L"CPlayerWalkState");
	_vec.push_back(L"CPlayerStartState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CPlayerIdleState" == _strStateName)
		return new CPlayerIdleState;
	if (L"CPlayerWalkState" == _strStateName)
		return new CPlayerWalkState;
	if (L"CPlayerStartState" == _strStateName)
		return new CPlayerStartState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new CPlayerIdleState;
		break;
	case (UINT)STATE_TYPE::PLAYERWALKSTATE:
		return new CPlayerWalkState;
		break;
	case (UINT)STATE_TYPE::PLAYERSTARTSTATE:
		return new CPlayerStartState;
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

	case STATE_TYPE::PLAYERWALKSTATE:
		return L"CPlayerWalkState";
		break;

	case STATE_TYPE::PLAYERSTARTSTATE:
		return L"CPlayerStartState";
		break;

	}
	return nullptr;
}
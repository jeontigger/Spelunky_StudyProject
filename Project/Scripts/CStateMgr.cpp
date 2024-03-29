#include "pch.h"
#include "CStateMgr.h"

#include "CPlayerIdleState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CPlayerIdleState");
}

CState * CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CPlayerIdleState" == _strStateName)
		return new CPlayerIdleState;
	return nullptr;
}

CState * CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::PLAYERIDLESTATE:
		return new CPlayerIdleState;
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

	}
	return nullptr;
}
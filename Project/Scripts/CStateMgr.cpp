#include "pch.h"
#include "CStateMgr.h"

#include "CPlayerIdleState.h"
#include "CPlayerDownState.h"
#include "CPlayerStartState.h"
#include "CSnakeEntryState.h"
#include "CSnakeIdleState.h"
#include "CSnakeAttackState.h"
#include "CPlayerJumpUpState.h"
#include "CPlayerFallDownState.h"
#include "CPlayerWalkState.h"
#include "CPlayerThrowState.h"
#include "CPlayerAttackState.h"
#include "CPlayerLadderState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CPlayerIdleState");
	_vec.push_back(L"CPlayerDownState");
	_vec.push_back(L"CPlayerStartState");
	_vec.push_back(L"CSnakeEntryState");
	_vec.push_back(L"CSnakeIdleState");
	_vec.push_back(L"CSnakeAttackState");
	_vec.push_back(L"CPlayerJumpUpState");
	_vec.push_back(L"CPlayerFallDownState");
	_vec.push_back(L"CPlayerWalkState");
	_vec.push_back(L"CPlayerThrowState");
	_vec.push_back(L"CPlayerAttackState");
	_vec.push_back(L"CPlayerLadderState");
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
	if (L"CPlayerJumpUpState" == _strStateName)
		return new CPlayerJumpUpState;
	if (L"CPlayerFallDownState" == _strStateName)
		return new CPlayerFallDownState;
	if (L"CPlayerWalkState" == _strStateName)
		return new CPlayerWalkState;
	if (L"CPlayerThrowState" == _strStateName)
		return new CPlayerThrowState;
	if (L"CPlayerAttackState" == _strStateName)
		return new CPlayerAttackState;
	if (L"CPlayerLadderState" == _strStateName)
		return new CPlayerLadderState;
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
	case (UINT)STATE_TYPE::PLAYERJUMPUPSTATE:
		return new CPlayerJumpUpState;
		break;
	case (UINT)STATE_TYPE::PLAYERFALLDOWNSTATE:
		return new CPlayerFallDownState;
		break;
	case (UINT)STATE_TYPE::PLAYERWALKSTATE:
		return new CPlayerWalkState;
		break;
	case (UINT)STATE_TYPE::PLAYERTHROWSTATE:
		return new CPlayerThrowState;
		break;
	case (UINT)STATE_TYPE::PLAYERATTACKSTATE:
		return new CPlayerAttackState;
		break;
	case (UINT)STATE_TYPE::PLAYERLADDERSTATE:
		return new CPlayerLadderState;
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

	case STATE_TYPE::PLAYERJUMPUPSTATE:
		return L"CPlayerJumpUpState";
		break;

	case STATE_TYPE::PLAYERFALLDOWNSTATE:
		return L"CPlayerFallDownState";
		break;

	case STATE_TYPE::PLAYERWALKSTATE:
		return L"CPlayerWalkState";
		break;

	case STATE_TYPE::PLAYERTHROWSTATE:
		return L"CPlayerThrowState";
		break;

	case STATE_TYPE::PLAYERATTACKSTATE:
		return L"CPlayerAttackState";
		break;

	case STATE_TYPE::PLAYERLADDERSTATE:
		return L"CPlayerLadderState";
		break;

	}
	return nullptr;
}
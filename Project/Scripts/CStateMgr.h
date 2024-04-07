#pragma once

#include <vector>
#include <string>

enum class STATE_TYPE
{
	PLAYERIDLESTATE,
	PLAYERDOWNSTATE,
	PLAYERSTARTSTATE,
	SNAKEENTRYSTATE,
	SNAKEIDLESTATE,
	SNAKEATTACKSTATE,
	PLAYERJUMPUPSTATE,
	PLAYERFALLDOWNSTATE,
	END,
};

using namespace std;

class CState;

class CStateMgr
{
public: 
	static void GetStateInfo(vector<wstring>& _vec);
	static CState* GetState(const wstring& _strStateName);
	static CState* GetState(UINT _iStateType);
	static const wchar_t* GetStateName(CState* _pState);
};

#pragma once

#include <Engine/CState.h>

class CPlayerThrowState
	:public CState
{
private:
	class CGameObject* m_Player;
	class CPlayerScript* m_Script;

public:
	virtual void finaltick();
	virtual void Enter();
	virtual void Exit();

public:
	CPlayerThrowState();
	~CPlayerThrowState();
};


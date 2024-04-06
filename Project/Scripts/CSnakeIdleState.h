#pragma once

#include <Engine/CState.h>

class CSnakeIdleState
	:public CState
{
private:
	float m_fDuration;
	float m_fAccTime;

	CGameObject* m_pPlayer;
	CGameObject* m_pOwner;
	class CSnakeScript* m_pScript;

public:
	virtual void finaltick();
	virtual void Enter();
	virtual void Exit() {};

public:
	CSnakeIdleState();
	~CSnakeIdleState();
};


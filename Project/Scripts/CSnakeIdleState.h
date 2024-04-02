#pragma once

#include <Engine/CState.h>

class CSnakeIdleState
	:public CState
{
private:
	float m_fAttackRange;
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


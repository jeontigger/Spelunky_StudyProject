#pragma once

#include <Engine/CState.h>

class CSnakeIdleState
	:public CState
{

public:
	virtual void finaltick() {};
	virtual void Enter();
	virtual void Exit() {};

public:
	CSnakeIdleState();
	~CSnakeIdleState();
};


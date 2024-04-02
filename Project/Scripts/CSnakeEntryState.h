#pragma once

#include <Engine/CState.h>

class CSnakeEntryState
	: public CState
{
public:
	virtual void finaltick() {};
	virtual void Enter();
	virtual void Exit();

public:
	CSnakeEntryState();
	~CSnakeEntryState();
};


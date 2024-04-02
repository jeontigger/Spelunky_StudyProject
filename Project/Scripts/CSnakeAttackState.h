#pragma once
#include <Engine/CState.h>

class CSnakeAttackState :
    public CState
{
public:
    virtual void finaltick() {};
    virtual void Enter(){};
    virtual void Exit(){};

public:
    CSnakeAttackState();
    ~CSnakeAttackState();
};


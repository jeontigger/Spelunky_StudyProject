#pragma once
#include <Engine/CState.h>
class CPlayerStartState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CPlayerStartState();
    ~CPlayerStartState();
};


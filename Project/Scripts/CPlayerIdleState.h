#pragma once
#include <Engine/CState.h>

class CPlayerIdleState :
    public CState
{
public:
    virtual void finaltick() {}
    virtual void Enter() {}
    virtual void Exit() {}

public:
    CPlayerIdleState();
    ~CPlayerIdleState();
};


#pragma once
#include <Engine/CState.h>
class CPlayerWalkState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit() {}

public:
    CPlayerWalkState();
    ~CPlayerWalkState();
};


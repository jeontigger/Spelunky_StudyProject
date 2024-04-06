#pragma once
#include <Engine/CState.h>
class CPlayerDownState :
    public CState
{
public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit() {}

public:
    CPlayerDownState();
    ~CPlayerDownState();
};


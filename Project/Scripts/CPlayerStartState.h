#pragma once
#include <Engine/CState.h>
class CPlayerStartState :
    public CState
{
private:
    int m_temp;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CPlayerStartState();
    ~CPlayerStartState();
};


#pragma once
#include <Engine/CState.h>

class CPlayerIdleState :
    public CState
{
private:
    CGameObject* m_Player;
    class CPlayerScript* m_PlayerScript;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit() {}

public:
    CPlayerIdleState();
    ~CPlayerIdleState();

private:

};


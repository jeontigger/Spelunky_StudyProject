#pragma once
#include <Engine/CState.h>

class CSnakeAttackState :
    public CState
{
private:
    float m_fDuration;

private:
    CGameObject* m_pPlayer;
    CGameObject* m_pOwner;
    class CSnakeScript* m_pScript;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit(){};

public:
    CSnakeAttackState();
    ~CSnakeAttackState();
};


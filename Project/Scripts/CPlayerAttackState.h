#pragma once
#include <Engine/CState.h>
class CPlayerAttackState :
    public CState
{
private:
    class CGameObject* m_Player;
    class CPlayerScript* m_Script;
    class CWhip* m_Whip;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerAttackState();
    ~CPlayerAttackState();
};


#pragma once
#include <Engine/CState.h>
class CPlayerFallDownState :
    public CState
{
private:
    class CGameObject* m_Player;
    class CPlayerScript* m_Script;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CPlayerFallDownState();
    ~CPlayerFallDownState();
};


#pragma once
#include <Engine/CState.h>

class CPlayerWalkState :
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
    CPlayerWalkState();
    ~CPlayerWalkState();
};


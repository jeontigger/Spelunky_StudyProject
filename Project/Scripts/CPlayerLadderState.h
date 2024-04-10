#pragma once
#include <Engine/CState.h>

class CPlayerLadderState :
    public CState
{
private:
    float m_fPlayerLadderSpeed;

private:
    class CGameObject* m_Player;
    class CPlayerScript* m_Script;

public:
    virtual void finaltick() override;
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CPlayerLadderState();
    ~CPlayerLadderState();
};


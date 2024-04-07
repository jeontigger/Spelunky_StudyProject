#pragma once
#include <Engine/CState.h>
class CPlayerDownState :
    public CState
{
private:
    class CGameObject* m_Player;
    class CPlayerScript* m_Script;

    float m_fCameraDown;
    float m_fCameraDownTimer;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit() {}

public:
    CPlayerDownState();
    ~CPlayerDownState();
};


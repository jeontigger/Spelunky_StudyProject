#pragma once
#include <Engine/CState.h>
class CPlayerDownState :
    public CState
{
private:
    Vec2 m_ChangeColliderPos;
    Vec2 m_ChangeColliderScale;
    Vec2 m_OriginColliderPos;
    Vec2 m_OriginColliderScale;

private:
    class CGameObject* m_Player;
    class CPlayerScript* m_Script;

    float m_fCameraDown;
    float m_fCameraDownTimer;

public:
    virtual void finaltick();
    virtual void Enter();
    virtual void Exit();

public:
    CPlayerDownState();
    ~CPlayerDownState();
};


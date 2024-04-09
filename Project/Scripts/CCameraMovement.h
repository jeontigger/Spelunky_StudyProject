#pragma once
#include <Engine/CScript.h>

class CCameraMovement :
    public CScript
{
private:
    float m_fShakingTimer;
    int m_iShakingPower;

public:
    void SetShakingTime(float _time) { m_fShakingTimer = _time; }
    void SetShakingPower(int _power) { m_iShakingPower = _power; }
    void Shake(float _time, int _power);

private:
    float m_fSpeed;
    Vec3 m_vPrevPos;
    Vec3 m_vMoveDir;

    CGameObject* m_Target;
    Vec3 m_vTargetPos;
    bool m_bCameraWallBlocked;
    bool m_bCameraPlatformBlocked;

public:
    void SetTarget(CGameObject* _target);
    void SetTarget(Vec3 _target);

public:
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};

    CLONE(CCameraMovement);
public:
    CCameraMovement();
    ~CCameraMovement();

private:
    void TargetTracking();
    void CameraMoving();
};


#pragma once
#include <Engine/CScript.h>
class CBombExplosion :
    public CScript
{
private:
    float m_fStartScale;
    float m_fIncreaseSpeed;
    float m_fForce;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CBombExplosion);
    CBombExplosion();
    ~CBombExplosion();
};


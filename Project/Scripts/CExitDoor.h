#pragma once
#include <Engine/CScript.h>
class CExitDoor :
    public CScript
{
private:
    CGameObject* m_KeyTex;
    CGameObject* m_Player;



public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CExitDoor);
    CExitDoor();
    ~CExitDoor();
};


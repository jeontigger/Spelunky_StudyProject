#pragma once
#include "CDetectCollider.h"
class CPlayerHitCollider :
    public CDetectCollider
{
public:
    virtual void Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale);

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CPlayerHitCollider();
    ~CPlayerHitCollider();
};


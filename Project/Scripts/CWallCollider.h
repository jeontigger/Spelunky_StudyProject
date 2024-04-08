#pragma once
#include "CDetectCollider.h"
class CWallCollider :
    public CDetectCollider
{
public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CWallCollider();
    ~CWallCollider();
};


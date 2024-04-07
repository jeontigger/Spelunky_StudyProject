#pragma once
#include "CDetectCollider.h"
class CCeilCollider :
    public CDetectCollider
{
public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CCeilCollider();
    ~CCeilCollider();
};


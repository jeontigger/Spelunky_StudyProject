#pragma once
#include "CFieldObject.h"
class CItem :
    public CFieldObject
{
private:
    class CPlayerScript* m_PlayerScript;

public:
    void SetPlayerScript(CPlayerScript* _player);
    void OutPlayerScript();
    void PutDown();

public:
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CLONE(CItem);
    CItem(UINT type);
    ~CItem();
};


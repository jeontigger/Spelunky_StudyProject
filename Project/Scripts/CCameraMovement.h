#pragma once
#include <Engine/CScript.h>

class CCameraMovement :
    public CScript
{
private:
    float m_fSpeed;
    Vec3 m_vPrevPos;
    Vec3 m_vMoveDir;

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
};


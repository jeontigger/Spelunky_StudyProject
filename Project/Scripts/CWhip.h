#pragma once
#include <Engine/CScript.h>
class CWhip :
    public CScript
{
public:
    void Attack();

    Ptr<CSound> m_pSound;

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}

    virtual void SaveToFile(FILE* _File) {}
    virtual void SaveToFile(ofstream& _File) {}
    virtual void LoadFromFile(FILE* _File) {}
    virtual void LoadFromFile(ifstream & _File) {}

public:
    CLONE(CWhip);
    CWhip();
    ~CWhip();
};


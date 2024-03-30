#pragma once

#include "CFieldObject.h"

class CPlayerScript :
    public CFieldObject
{
private:

public:
    virtual void skill() override;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);


    virtual void SaveToFile(FILE* _File) override {};
    virtual void SaveToFile(ofstream& fout) override {};
    virtual void LoadFromFile(FILE* _File) override {};
    virtual void LoadFromFile(ifstream& fin) override {};

    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};


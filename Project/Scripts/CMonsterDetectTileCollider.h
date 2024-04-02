#pragma once
#include <Engine/CScript.h>
class CMonsterDetectTileCollider :
    public CScript
{
private:
    class CGameObject* m_parent;

    int m_iTileCnt;

public:
    void Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale);
    bool DetectTile() { 
        return m_iTileCnt > 0;
    }

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};
public:
    CLONE(CMonsterDetectTileCollider);
    CMonsterDetectTileCollider();
    ~CMonsterDetectTileCollider();
};


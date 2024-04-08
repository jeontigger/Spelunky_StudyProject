#pragma once
#include <Engine/CScript.h>
class CDetectCollider :
    public CScript
{
protected:
    class CGameObject* m_parent;

public:
    CGameObject* GetParent() { return m_parent; }
    void SetName(const string& _name);

protected:
    int m_iTileCnt;
    int m_iPlayerCnt;

public:
    virtual void Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale);
    bool DetectTile() { 
        return m_iTileCnt > 0;
    }
    bool DetectPlayer() { return m_iPlayerCnt > 0; }

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};
public:
    CLONE(CDetectCollider);
    CDetectCollider();
    CDetectCollider(UINT _type);
    ~CDetectCollider();
};


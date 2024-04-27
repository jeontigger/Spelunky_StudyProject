#pragma once

#include <Engine/CScript.h>

class CFieldObject :
    public CScript
{

private:
    bool isPlayer;

public:
    void ImPlayer() { isPlayer = true; }

protected:
    vector<CGameObject*> m_Ground;
    bool m_bLeftBump;
    int m_bRightBump;
    int m_iTileCnt;
    bool m_bJump;

public:
    void AddOverlapGround(CGameObject* _pObejct);
    void SubOverlapGround(CGameObject* _pObejct);

    inline bool IsGrounded() { return m_Ground.size() > 0; }

    inline void SetLeftBump(bool _b) { _b ? m_bLeftBump = true : m_bLeftBump = false; }
    inline bool IsLeftBump() { return m_bLeftBump > 0; }
    inline void SetRightBump(bool _b) { _b ? m_bRightBump = true : m_bRightBump = false; }
    inline bool IsRightBump() { return m_bRightBump > 0; }

public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void skill(Vec2 _force);

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override {};
    virtual void SaveToFile(ofstream& fout) override {};
    virtual void LoadFromFile(FILE* _File) override {};
    virtual void LoadFromFile(ifstream& fin) override {};

public:
    CFieldObject(UINT type);
    ~CFieldObject();

private:
    // 중력 계산
    void AddGravity();
    
    // 움직임

};


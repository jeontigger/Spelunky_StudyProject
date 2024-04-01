#pragma once

#include "CFieldObject.h"

class CPlayerScript :
    public CFieldObject
{
private:
    float m_fRunSpeed;
    bool m_bLastMoveDir; // 0 : left, 1 : right
    bool m_bMoveLeft;
    bool m_bMoveRight;

public:
    bool IsLookRight();
    void MoveLeft();
    void MoveRight();
    bool IsMoving() { 
        return m_bMoveRight || m_bMoveLeft;
    }

private:
    float m_fJumpInitSpeed;
    float m_fJumpWeightSpeed;
    float m_fJumpMaxTime;
    float m_fJumpTimer;
    bool m_bJumpup;

public:
    void Jump();
    bool IsJumpUp() { return m_bJumpup; }

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

    friend class CPlayerIdleState;
};


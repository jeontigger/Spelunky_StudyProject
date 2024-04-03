#pragma once

#include "CCharacterScript.h"

class CPlayerScript :
    public CCharacterScript
{
public:
    virtual void Hit(int _damage) override;

private:
    PlayerKey InputKey;

public:
    PlayerKey GetInputKeys() { return InputKey; }
    void SetInputKey(PlayerKey _key) { InputKey = _key; }

private:
    Vec3 m_vPrevPos;
    Vec3 m_vCurPos;

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


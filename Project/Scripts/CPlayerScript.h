#pragma once

#include "CCharacterScript.h"

class CPlayerScript :
    public CCharacterScript
{
private:
    class CPlayerHitCollider* m_HitCollider;
    float m_fInvincibility;
    float m_fInvincibilityTimer;
    float m_fJumpDelayTimer;

private:
    class CItem* m_HandleItem;

private:
    PlayerKey InputKey;

    Vec3 m_vPrevPos;
    Vec3 m_vCurPos;
    Vec3 m_vSocketPos;

public:
    PlayerKey GetInputKeys() { return InputKey; }
    void SetInputKey(PlayerKey _key) { InputKey = _key; }

    Vec3 GetSocketPos() { return m_vSocketPos; }
    void SetSocketPos(Vec3 _pos) { m_vSocketPos = _pos; }

public:
    bool IsMoving();
    bool IsHandling();
    Vec3 GetItemSocketPos();

    void HandOn(CGameObject* item);
    void PutDown();

public:
    virtual void Hit(int _damage) override;

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

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    ~CPlayerScript();

    friend class CPlayerIdleState;
    friend class CPlayerDownState;

};


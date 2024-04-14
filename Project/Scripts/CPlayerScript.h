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

    int m_iLadderCnt;
    Vec3 m_vRecentLadderPos;

private:
    class CItem* m_HandleItem;
    class CWhip* m_Whip;

    PlayerKey InputKey;

    Vec3 m_vPrevPos;
    Vec3 m_vCurPos;
    Vec3 m_vSocketPos;
    Vec2 m_FrontForce;
    Vec2 m_UpForce;
    Vec2 m_DownForce;

private:
    int m_iBombCnt;
    int m_iRopeCnt;

public:
    int GetBombCnt() { return m_iBombCnt; }
    int GetRopeCnt() { return m_iRopeCnt; }

public:
    CWhip* GetWhip() { return m_Whip; }

    PlayerKey GetInputKeys() { return InputKey; }
    void SetInputKey(PlayerKey _key) { InputKey = _key; }

    Vec3 GetSocketPos() { return m_vSocketPos; }
    void SetSocketPos(Vec3 _pos) { m_vSocketPos = _pos; }

    void CloudSpawn();

public:
    bool IsMoving();
    bool IsHandling();
    Vec3 GetItemSocketPos();
    bool DetectLadder();
    Vec3 GetDetectLadderPos() { return m_vRecentLadderPos; }

    void HandOn(CGameObject* item);
    void PutDown();

public:
    void Bomb();

public:
    virtual void Hit(int _damage) override;
    virtual void Skill();
    virtual void Attack();

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


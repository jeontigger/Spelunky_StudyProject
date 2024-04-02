#pragma once

#include <Engine/CScript.h>

class CFieldObject :
    public CScript
{
private:
    bool isPlayer;

public:
    void ImPlayer() { isPlayer = true; }

private:
    float m_fMass;
    float m_fGravity;
    Vec3 m_vPos;
    Vec3 m_vPrevPos;
    Vec2 m_vVelocity;

protected:
    int m_bGround;
    bool m_bLeftBump;
    int m_bRightBump;
    int m_iTileCnt;

public:
    inline void SetMass(UINT _mass) { m_fMass = _mass; }
    inline UINT GetMass() { return m_fMass; }

    inline void SetGravity(float _gravity) { m_fGravity = _gravity; }
    inline float GetGravity() { return m_fGravity; }

    inline bool IsMove() { return m_fGravity != 0.f; }

    inline void SetGround(bool _b) { _b? m_bGround++ : m_bGround--; }
    inline bool IsGrounded() { return m_bGround > 0; }

    inline void SetLeftBump(bool _b) { _b ? m_bLeftBump = true : m_bLeftBump = false; }
    inline bool IsLeftBump() { return m_bLeftBump > 0; }
    inline void SetRightBump(bool _b) { _b ? m_bRightBump = true : m_bRightBump = false; }
    inline bool IsRightBump() { return m_bRightBump > 0; }


    Vec2 GetVelocity() { return m_vVelocity; }
    void SetVelocity(Vec2 _vec) { m_vVelocity = _vec; }
    void AddVelocity(Vec2 _vec) { m_vVelocity += _vec; }

public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void skill() = 0;

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

public:
    CFieldObject(UINT type);
    ~CFieldObject();

private:
    // 중력 계산
    void AddGravity();
    
    // 움직임

};


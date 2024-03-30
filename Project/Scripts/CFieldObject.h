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
    bool m_bGround;

public:
    inline void SetMass(UINT _mass) { m_fMass = _mass; }
    inline UINT GetMass() { return m_fMass; }

    inline void SetGravity(float _gravity) { m_fGravity = _gravity; }
    inline float GetGravity() { return m_fGravity; }

    inline bool IsMove() { return m_fGravity != 0.f; }

    inline void SetGround(bool _b) { m_bGround = _b; }
    inline bool IsGrounded() { return m_bGround; }

public:
    virtual void tick() override;
    virtual void begin() override;
    virtual void skill() = 0;

public:
    CFieldObject(UINT type);
    ~CFieldObject();

private:
    // 중력 계산
    void AddGravity();
    
    // 움직임

};


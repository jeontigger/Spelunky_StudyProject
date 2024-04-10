#pragma once

#include <Engine/CScript.h>

class CFieldObject :
    public CScript
{
protected:
    class CDetectCollider* m_ButtomCollider;
    class CDetectCollider* m_BackCollider;
    class CDetectCollider* m_FrontCollider;
    class CDetectCollider* m_TopCollider;

private:
    bool isPlayer;

public:
    void ImPlayer() { isPlayer = true; }

protected:
    float m_fMass;
    float m_fGravity;
    bool m_bUseGravity;
    bool m_bUseVelocityX;
    bool m_bUseVelocityY;

    float m_fAirFriction;
    float m_fGroundFriction;
    Vec3 m_vPos;
    Vec3 m_vPrevPos;
    Vec2 m_vVelocity;

protected:
    bool m_bGround;
    bool m_bLeftBump;
    int m_bRightBump;
    int m_iTileCnt;

public:
    inline void SetMass(UINT _mass) { m_fMass = _mass; }
    inline UINT GetMass() { return m_fMass; }

    inline void SetGravity(float _gravity) { m_fGravity = _gravity; }
    inline float GetGravity() { return m_fGravity; }
    inline void UseGravity(bool _use) { m_bUseGravity = _use; }
    inline void UseVelocityX(bool _use) { m_bUseVelocityX= _use; }
    inline void UseVelocityY(bool _use) { m_bUseVelocityY = _use; }

    void Stop() { m_vVelocity.x = 0.f; }
    inline bool IsMove() { return m_fGravity != 0.f; }

    inline void SetGround(bool _b) { m_bGround = _b; }
    inline bool IsGrounded() { 
        return m_bGround > 0; }

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


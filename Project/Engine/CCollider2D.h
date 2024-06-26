#pragma once
#include "CComponent.h"

enum class COLLIDER2D_TYPE 
{
    RECT,
    CIRCLE,
};


class CCollider2D :
    public CComponent
{
private:
    bool            m_bActive;

public:
    void Activate(bool _b) { m_bActive = _b; }
    bool IsActivate() { return m_bActive; }

private:
    b2Body* m_Body;
    b2Fixture* m_Fixture;

public:
    void BodyInit(bool _isDynamic);
    b2Body* GetBody() { return m_Body; }

private:
    Vec3            m_vOffsetPos;
    Vec3            m_vOffsetScale;
    int             m_CollisionCount;   // 다른 충돌체와 충돌중인 횟수
    float m_fRadius;
    bool            m_bAbsolute;

    Matrix          m_matColWorld;
    COLLIDER2D_TYPE m_Type;    

public:
    void SetAbsolute(bool _bAbsol) { m_bAbsolute = _bAbsol; }
    void SetOffsetPos(Vec2 _vOffset) { m_vOffsetPos = Vec3(_vOffset.x, _vOffset.y, 0.f); }
    void SetOffsetScale(Vec2 _vOffsetScale);
    void SetColliderType(COLLIDER2D_TYPE _Type) { m_Type = _Type; }
    void SetRadius(float _radius) { m_fRadius = _radius; }
    float GetRadius() { return m_fRadius; }

    bool IsAbsolute() { return m_bAbsolute; }
    Vec2 GetOffsetPos() { return Vec2(m_vOffsetPos.x, m_vOffsetPos.y); }
    Vec2 GetOffsetScale() { return Vec2(m_vOffsetScale.x, m_vOffsetScale.y); }

    Vec2 GetRelativePos();
    Vec2 GetRelativeScale();
    COLLIDER2D_TYPE GetType() { return m_Type; }

    const Matrix& GetColliderWorldMat() { return m_matColWorld; }

public:
    virtual void finaltick() override;


public:
    void BeginOverlap(CCollider2D* _OtherCollider);
    void Overlap(CCollider2D* _OtherCollider);
    void EndOverlap(CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void SaveToFile(ofstream& fout) override;
    virtual void LoadFromFile(FILE* _File) override;
    virtual void LoadFromFile(ifstream& fin) override;

    CLONE(CCollider2D);
public:
    CCollider2D();
    CCollider2D(const CCollider2D& _OriginCollider2D);
    ~CCollider2D();
};


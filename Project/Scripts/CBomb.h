#pragma once
#include "CItem.h"
class CBomb :
    public CItem
{
private:
    float m_fBombTimer;
    float m_fScaleTimer;
    float m_fScaleTime;
    float m_fScaleReduceSpeed;

    float m_fAnimationChangeStart;
    float m_fAnimationChangeTimer;
    float m_fAnimationChangeTime;
    int m_iAnimationCnt;

    Vec3 m_vOriginScale;

public:
    void Bomb();

public:
    virtual void tick() override;
    virtual void begin() override;

public:
    CLONE(CBomb);
    CBomb();
    ~CBomb();
};



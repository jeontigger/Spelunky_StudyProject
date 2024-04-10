#pragma once
#include <Engine/CScript.h>
class CParticleOnce :
    public CScript
{
private:
    float m_acctime;
    float m_fDeleteTime;
    bool m_bInfinite;

public:
    void SetTimer(float _time) { m_fDeleteTime = _time; }
    void Infinite(bool _infinite) { m_bInfinite = _infinite; }

public:
    static CGameObject* Instantiate(const wstring& _prefKey, const wstring& _atlasKey);

public:
    virtual void tick() override;

public:
    CLONE(CParticleOnce);
    CParticleOnce();
    ~CParticleOnce();
};


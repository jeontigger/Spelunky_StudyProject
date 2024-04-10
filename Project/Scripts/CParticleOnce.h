#pragma once
#include <Engine/CScript.h>
class CParticleOnce :
    public CScript
{
private:
    float m_acctime;

public:
    static CGameObject* Instantiate(const wstring& _prefKey, const wstring& _atlasKey);

public:
    virtual void tick() override;

public:
    CLONE(CParticleOnce);
    CParticleOnce();
    ~CParticleOnce();
};


#pragma once
#include "CRenderComponent.h"

#include "CParticleUpdate.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*      m_ParticleBuffer;
    UINT                    m_MaxParticleCount;

    tParticleModule         m_Module;
    CStructuredBuffer*      m_ParticleModuleBuffer;

    CStructuredBuffer*      m_SpawnCountBuffer;

    Ptr<CParticleUpdate>    m_CSParticleUpdate;

    Ptr<CTexture>           m_ParticleTex;

    float                   m_Time;

public:
    void SetParticleTex(const wstring& _texName);
    void SetParticleTex(Ptr<CTexture> _tex) { m_ParticleTex = _tex; }
    void SetMaxParticleCount(int _count) { m_MaxParticleCount = _count; }
    void SetSpawnRate(int _rate) { m_Module.SpawnRate = _rate; }

public:
    virtual void UpdateData() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToFile(ofstream& fout) override;
    virtual void LoadFromFile(ifstream& fin) override;
    CLONE(CParticleSystem);
public:
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _OriginParticle);
    ~CParticleSystem();

    friend class ParticleUI;
};


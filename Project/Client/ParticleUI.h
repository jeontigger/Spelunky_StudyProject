#pragma once
#include "ComponentUI.h"
class ParticleUI :
    public ComponentUI
{
private:
    class CParticleSystem* m_Particle;

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    ParticleUI();
    ~ParticleUI();
};


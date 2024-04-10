#include "pch.h"
#include "ParticleUI.h"

ParticleUI::ParticleUI()
	: ComponentUI("Particle", UIParticleSystemName, COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetComponentTitle("ParticleSystem");
	SetSize(ImVec2(0, 40));
}

ParticleUI::~ParticleUI()
{
}

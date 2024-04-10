#include "pch.h"
#include "ParticleUI.h"

#include <Engine/CParticleSystem.h>

ParticleUI::ParticleUI()
	: ComponentUI("Particle", UIParticleSystemName, COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetComponentTitle("ParticleSystem");
	SetSize(ImVec2(0, 500));
}

ParticleUI::~ParticleUI()
{
}

void ParticleUI::Activate()
{
	ComponentUI::Activate();

	m_Particle = GetTargetObject()->ParticleSystem();
}

void ParticleUI::render_update()
{
	ComponentUI::render_update();

	// �ִ� ��ȯ ����
	int MaxParticleCount = m_Particle->m_MaxParticleCount;
	ImGui::DragInt("MaxParticleCount", &MaxParticleCount);
	m_Particle->m_MaxParticleCount = MaxParticleCount;

	// �̹��� �ε���
	int AtlasIdx = m_Particle->m_Module.AtlasIdx;
	ImGui::InputInt("AtlasIdx", &AtlasIdx);
	m_Particle->m_Module.AtlasIdx = AtlasIdx;

	bool SpawnModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN];
	ImGui::Checkbox("SpawnModule", &SpawnModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = SpawnModule;

	// ��ȯ ����
	Vec2 SpawnArange = Vec2(m_Particle->m_Module.vSpawnBoxScale.x, m_Particle->m_Module.vSpawnBoxScale.y);
	ImGui::DragFloat2("SpawnArange", (float*)&SpawnArange);
	m_Particle->m_Module.vSpawnBoxScale.x = SpawnArange.x;
	m_Particle->m_Module.vSpawnBoxScale.y = SpawnArange.y;

	// ��ȯ �ּ� ũ��
	float SpawnMinScale = m_Particle->m_Module.vSpawnMinScale.x;
	ImGui::DragFloat("SpawnMinScale", &SpawnMinScale);
	m_Particle->m_Module.vSpawnMinScale.x = SpawnMinScale;
	m_Particle->m_Module.vSpawnMinScale.y = SpawnMinScale;

	// ��ȯ �ִ� ũ��
	float SpawnMaxScale = m_Particle->m_Module.vSpawnMaxScale.x;
	ImGui::DragFloat("SpawnMaxScale", &SpawnMaxScale);
	m_Particle->m_Module.vSpawnMaxScale.x = SpawnMaxScale;
	m_Particle->m_Module.vSpawnMaxScale.y = SpawnMaxScale;

	// ���ӽð� �ּ� & �ִ� ũ��
	float MinLifeDuration = m_Particle->m_Module.MinLife;
	float MaxLifeDuration = m_Particle->m_Module.MaxLife;

	if (ImGui::DragFloat("MinLifeDuration", &MinLifeDuration)) {
		if (MinLifeDuration > MaxLifeDuration) {
			MaxLifeDuration = MinLifeDuration;
		}
	}
	if (ImGui::DragFloat("MaxLifeDuration", &MaxLifeDuration)) {
		if (MaxLifeDuration < MinLifeDuration) {
			MinLifeDuration = MaxLifeDuration;
		}
	}
	m_Particle->m_Module.MinLife = MinLifeDuration;
	m_Particle->m_Module.MaxLife = MaxLifeDuration;

	// ���� �ּ� & �ִ� ũ��
	float MinMass = m_Particle->m_Module.MinMass;
	float MaxMass = m_Particle->m_Module.MaxMass;

	if (ImGui::DragFloat("MinMass", &MinMass)) {
		if (MinMass > MaxMass) {
			MaxMass = MinMass;
		}
	}
	if (ImGui::DragFloat("MaxMass", &MaxMass)) {
		if (MaxMass < MinMass) {
			MinMass = MaxMass;
		}
	}
	m_Particle->m_Module.MinMass = MinMass;
	m_Particle->m_Module.MaxMass = MaxMass;

	// ��ȯ ����
	int SpawnRate = m_Particle->m_Module.SpawnRate;
	ImGui::DragInt("SpawnRate", &SpawnRate);
	m_Particle->m_Module.SpawnRate = SpawnRate;

	// �ӵ� ��� ��/����
	bool velocityModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY];
	ImGui::Checkbox("VelocityModule", &velocityModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = velocityModule;

	// �ӵ� ���� Ÿ��
	int AddVelocityType = m_Particle->m_Module.AddVelocityType;
	ImGui::InputInt("AddVelocityType", &AddVelocityType);
	m_Particle->m_Module.AddVelocityType = AddVelocityType;

	// �ӵ� �ּ� �ִ� ũ��
	float MinSpeed = m_Particle->m_Module.MinSpeed;
	float MaxSpeed = m_Particle->m_Module.MaxSpeed;

	if (ImGui::DragFloat("MinSpeed", &MinSpeed)) {
		if (MinSpeed > MaxSpeed) {
			MaxSpeed = MinSpeed;
		}
	}
	if (ImGui::DragFloat("MaxSpeed", &MaxSpeed)) {
		if (MaxSpeed < MinSpeed) {
			MinSpeed = MaxSpeed;
		}
	}
	m_Particle->m_Module.MinSpeed = MinSpeed;
	m_Particle->m_Module.MaxSpeed = MaxSpeed;

	// ���� Ÿ��
	int VelocityAlignment = m_Particle->m_Module.VelocityAlignment;
	ImGui::InputInt("VelocityAlignment", &VelocityAlignment);
	m_Particle->m_Module.VelocityAlignment = VelocityAlignment;

	// ���� ���� Ÿ��
	int AlphaBasedLife = m_Particle->m_Module.AlphaBasedLife;
	ImGui::InputInt("AlphaBasedLife", &AlphaBasedLife);
	m_Particle->m_Module.AlphaBasedLife = AlphaBasedLife;


	// �� ��� ��/����
	bool ForceModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE];
	ImGui::Checkbox("ForceModule", &ForceModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = ForceModule;


	// �� ũ��
	float NoiseForceScale = m_Particle->m_Module.NoiseForceScale;
	ImGui::DragFloat("NoiseForceScale", &NoiseForceScale);
	m_Particle->m_Module.NoiseForceScale = NoiseForceScale;
}
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

	// 최대 소환 개수
	int MaxParticleCount = m_Particle->m_MaxParticleCount;
	ImGui::DragInt("MaxParticleCount", &MaxParticleCount);
	m_Particle->m_MaxParticleCount = MaxParticleCount;

	// 이미지 인덱스
	int AtlasIdx = m_Particle->m_Module.AtlasIdx;
	ImGui::InputInt("AtlasIdx", &AtlasIdx);
	m_Particle->m_Module.AtlasIdx = AtlasIdx;

	bool SpawnModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN];
	ImGui::Checkbox("SpawnModule", &SpawnModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = SpawnModule;

	// 소환 범위
	Vec2 SpawnArange = Vec2(m_Particle->m_Module.vSpawnBoxScale.x, m_Particle->m_Module.vSpawnBoxScale.y);
	ImGui::DragFloat2("SpawnArange", (float*)&SpawnArange);
	m_Particle->m_Module.vSpawnBoxScale.x = SpawnArange.x;
	m_Particle->m_Module.vSpawnBoxScale.y = SpawnArange.y;

	// 소환 최소 크기
	float SpawnMinScale = m_Particle->m_Module.vSpawnMinScale.x;
	ImGui::DragFloat("SpawnMinScale", &SpawnMinScale);
	m_Particle->m_Module.vSpawnMinScale.x = SpawnMinScale;
	m_Particle->m_Module.vSpawnMinScale.y = SpawnMinScale;

	// 소환 최대 크기
	float SpawnMaxScale = m_Particle->m_Module.vSpawnMaxScale.x;
	ImGui::DragFloat("SpawnMaxScale", &SpawnMaxScale);
	m_Particle->m_Module.vSpawnMaxScale.x = SpawnMaxScale;
	m_Particle->m_Module.vSpawnMaxScale.y = SpawnMaxScale;

	// 지속시간 최소 & 최대 크기
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

	// 질량 최소 & 최대 크기
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

	// 소환 비율
	int SpawnRate = m_Particle->m_Module.SpawnRate;
	ImGui::DragInt("SpawnRate", &SpawnRate);
	m_Particle->m_Module.SpawnRate = SpawnRate;

	// 속도 모듈 온/오프
	bool velocityModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY];
	ImGui::Checkbox("VelocityModule", &velocityModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = velocityModule;

	// 속도 방향 타입
	int AddVelocityType = m_Particle->m_Module.AddVelocityType;
	ImGui::InputInt("AddVelocityType", &AddVelocityType);
	m_Particle->m_Module.AddVelocityType = AddVelocityType;

	// 속도 최소 최대 크기
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

	// 렌더 타입
	int VelocityAlignment = m_Particle->m_Module.VelocityAlignment;
	ImGui::InputInt("VelocityAlignment", &VelocityAlignment);
	m_Particle->m_Module.VelocityAlignment = VelocityAlignment;

	// 렌더 알파 타입
	int AlphaBasedLife = m_Particle->m_Module.AlphaBasedLife;
	ImGui::InputInt("AlphaBasedLife", &AlphaBasedLife);
	m_Particle->m_Module.AlphaBasedLife = AlphaBasedLife;


	// 힘 모듈 온/오프
	bool ForceModule = m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE];
	ImGui::Checkbox("ForceModule", &ForceModule);
	m_Particle->m_Module.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = ForceModule;


	// 힘 크기
	float NoiseForceScale = m_Particle->m_Module.NoiseForceScale;
	ImGui::DragFloat("NoiseForceScale", &NoiseForceScale);
	m_Particle->m_Module.NoiseForceScale = NoiseForceScale;
}
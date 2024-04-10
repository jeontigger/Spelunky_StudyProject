#include "pch.h"
#include "ParticleUI.h"

#include <Engine/CParticleSystem.h>

ParticleUI::ParticleUI()
	: ComponentUI("Particle", UIParticleSystemName, COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetComponentTitle("ParticleSystem");
	SetSize(ImVec2(0, 200));
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


}


//struct tParticleModule
//{
//	// Sapwn 모듈
//	Vec4	vSpawnColor;	// 초기 컬러
//	Vec4	vSpawnMinScale;	// 초기 최소 크기
//	Vec4	vSpawnMaxScale;	// 초기 최대 크기		
//
//	float	MinLife;		// 최소 수명
//	float	MaxLife;		// 최대 수명
//	float	MinMass;		// 최소 질량
//	float	MaxMass;		// 최대 질량
//	int		SpawnRate;		// 초당 생성 개수
//	int		SpaceType;		// 좌표계(0 : LocalSpace, 1 : WorldSpace)
//	int		SpawnShape;		// 스폰 범위(0 : Sphere, 1 : Box)
//	float	Radius;			// SpawnShape 가 Sphere 인 경우, 반지름 길이
//	Vec4	vSpawnBoxScale;	// SpawnShape 가 Box 인 경우, Box 의 크기
//
//	// Add Velocity
//	int		AddVelocityType;// 0 : From Center, 1: To Center, 2: Fix Direction
//	float	MinSpeed;
//	float	MaxSpeed;
//	float	FixedAngle;		// 해당 방향에서 랜덤범위 각도
//	Vec4	FixedDirection;	// 지정 방향
//
//	// Scale
//	Vec4	vScaleRatio;
//
//	// Noise Force
//	float	NoiseForceScale;
//	float	NoiseForceTerm;
//
//	// Drag
//	float	DragTime;	// 감속시키는데 걸리는 시간
//
//	// Render
//	int		VelocityAlignment;  // 1 : On, 0 : Off
//	int		AlphaBasedLife;		// 0 : off, 1 : NomrlizedAge, 2: Age
//	float	AlphaMaxAge;
//
//	// Module On / Off
//	int arrModuleCheck[(UINT)PARTICLE_MODULE::END];
//
//	int AtlasIdx;
//
//	friend ofstream& operator<<(ofstream& fout, tParticleModule& module);
//	friend ifstream& operator>>(ifstream& fin, tParticleModule& module);
//};
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


}


//struct tParticleModule
//{
//	// Sapwn ���
//	Vec4	vSpawnColor;	// �ʱ� �÷�
//	Vec4	vSpawnMinScale;	// �ʱ� �ּ� ũ��
//	Vec4	vSpawnMaxScale;	// �ʱ� �ִ� ũ��		
//
//	float	MinLife;		// �ּ� ����
//	float	MaxLife;		// �ִ� ����
//	float	MinMass;		// �ּ� ����
//	float	MaxMass;		// �ִ� ����
//	int		SpawnRate;		// �ʴ� ���� ����
//	int		SpaceType;		// ��ǥ��(0 : LocalSpace, 1 : WorldSpace)
//	int		SpawnShape;		// ���� ����(0 : Sphere, 1 : Box)
//	float	Radius;			// SpawnShape �� Sphere �� ���, ������ ����
//	Vec4	vSpawnBoxScale;	// SpawnShape �� Box �� ���, Box �� ũ��
//
//	// Add Velocity
//	int		AddVelocityType;// 0 : From Center, 1: To Center, 2: Fix Direction
//	float	MinSpeed;
//	float	MaxSpeed;
//	float	FixedAngle;		// �ش� ���⿡�� �������� ����
//	Vec4	FixedDirection;	// ���� ����
//
//	// Scale
//	Vec4	vScaleRatio;
//
//	// Noise Force
//	float	NoiseForceScale;
//	float	NoiseForceTerm;
//
//	// Drag
//	float	DragTime;	// ���ӽ�Ű�µ� �ɸ��� �ð�
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
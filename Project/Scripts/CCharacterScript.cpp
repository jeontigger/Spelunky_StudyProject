#include "pch.h"
#include "CCharacterScript.h"

#include "CDetectCollider.h"
#include "CParticleOnce.h"

CCharacterScript::CCharacterScript(UINT type)
	: CFieldObject(type)
	, m_tInfo()
{
}

CCharacterScript::CCharacterScript(const CCharacterScript& _origin)
	:CFieldObject(_origin)
	, m_tInfo(_origin.m_tInfo)
{
}

CCharacterScript::~CCharacterScript()
{
}

void CCharacterScript::tick()
{
	CFieldObject::tick();
}

void CCharacterScript::begin()
{
	CFieldObject::begin();


}

void CCharacterScript::Hit(int _damage)
{
	m_tInfo.Health -= _damage;

	CGameObject* obj = CParticleOnce::Instantiate(ParticleBloodPrefKey, TexParticleSmallAtlas);
	obj->Transform()->SetRelativePos(Vec3(GetOwner()->Transform()->GetRelativePos().x, GetOwner()->Transform()->GetRelativePos().y, -1));
	GamePlayStatic::SpawnGameObject(obj, PlayerLayer);

	obj = CParticleOnce::Instantiate(ParticleStarPrefKey, TexParticleSmallAtlas);
	obj->Transform()->SetRelativePos(Vec3(GetOwner()->Transform()->GetRelativePos().x, GetOwner()->Transform()->GetRelativePos().y, -1));
	GamePlayStatic::SpawnGameObject(obj, PlayerLayer);

	if (m_tInfo.Health <= 0) {
		Die();
	}
}

bool CCharacterScript::IsLookRight()
{
	return GetOwner()->Transform()->GetRelativeRotation().y == 0;
}

void CCharacterScript::TurnLeft()
{
	Vec3 rotation = Transform()->GetRelativeRotation();
	rotation.y = -XM_PI;
	Transform()->SetRelativeRotation(rotation);
}

void CCharacterScript::TurnRight()
{
	Vec3 rotation = Transform()->GetRelativeRotation();
	rotation.y = 0;
	Transform()->SetRelativeRotation(rotation);
}

void CCharacterScript::MoveFront()
{
	if (IsLookRight()) {
		//m_vVelocity.x = m_tInfo.Speed;
	}
	else {
		//m_vVelocity.x = -m_tInfo.Speed;
	}

}


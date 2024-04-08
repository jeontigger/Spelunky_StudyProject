#include "pch.h"
#include "CCharacterScript.h"

#include "CDetectCollider.h"

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

	if (m_tInfo.Health <= 0) {
		Die();
	}
}

bool CCharacterScript::IsLookRight()
{
	return GetOwner()->Transform()->GetRelativeRotation().y >= 0;
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
	if (!m_FrontCollider->DetectTile()) {
		m_bMoveFront = true;
		if (IsLookRight()) {
			SetVelocity(Vec2(GetSpeed(), GetVelocity().y));
		}
		else {
			SetVelocity(Vec2(-GetSpeed(), GetVelocity().y));
		}
	}
}

void CCharacterScript::MoveBack()
{
	if (!m_BackCollider->DetectTile()) {
		m_bMoveBack = true;
	}
}

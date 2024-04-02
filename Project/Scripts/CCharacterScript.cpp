#include "pch.h"
#include "CCharacterScript.h"

void CCharacterScript::tick()
{
	CFieldObject::tick();
	// Move
	Vec2 vel = GetVelocity();
	if (m_bMoveRight && m_bMoveLeft) {
		m_bLastMoveDir ? m_bMoveLeft = false : m_bMoveRight = false;
	}

	if (m_bMoveRight) {
		vel.x = m_fRunSpeed;
		Vec3 rotation = Transform()->GetRelativeRotation();
		rotation.y = 0;
		Transform()->SetRelativeRotation(rotation);
	}

	if (m_bMoveLeft) {
		vel.x = -m_fRunSpeed;
		Vec3 rotation = Transform()->GetRelativeRotation();
		rotation.y = -XM_PI;
		Transform()->SetRelativeRotation(rotation);
	}

	if (!m_bMoveLeft && !m_bMoveRight) {
		vel.x = 0;
	}

	SetVelocity(vel);
}

CCharacterScript::CCharacterScript(UINT type)
	: CFieldObject(type)
	, m_fRunSpeed(6.f)
{
}

CCharacterScript::~CCharacterScript()
{
}

void CCharacterScript::Hit()
{
	int a = 0;
}

bool CCharacterScript::IsLookRight()
{
	return GetOwner()->Transform()->GetRelativeRotation().y >= 0;
}

void CCharacterScript::MoveLeft()
{
	m_bLastMoveDir = 0;
	m_bMoveLeft = true;
	Vec3 rotation = Transform()->GetRelativeRotation();
	rotation.y = -XM_PI;
	Transform()->SetRelativeRotation(rotation);
	if (IsRightBump()) {
		SetRightBump(false);
	}
}

void CCharacterScript::MoveRight()
{
	m_bLastMoveDir = 1;
	m_bMoveRight = true;
	Vec3 rotation = Transform()->GetRelativeRotation();
	rotation.y = 0;
	Transform()->SetRelativeRotation(rotation);
	if (IsLeftBump()) {
		SetLeftBump(false);
	}
}

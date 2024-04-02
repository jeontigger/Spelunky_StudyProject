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
		Vec3 scale = Transform()->GetRelativeScale();
		scale.x = abs(scale.x);
		Transform()->SetRelativeScale(scale);
	}

	if (m_bMoveLeft) {
		vel.x = -m_fRunSpeed;
		Vec3 scale = Transform()->GetRelativeScale();
		scale.x = -(abs(scale.x));
		Transform()->SetRelativeScale(scale);
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

bool CCharacterScript::IsLookRight()
{
	return m_bMoveRight;
}

void CCharacterScript::MoveLeft()
{
	m_bLastMoveDir = 0;
	m_bMoveLeft = true;
	if (IsRightBump()) {
		SetRightBump(false);
	}
}

void CCharacterScript::MoveRight()
{
	m_bLastMoveDir = 1;
	m_bMoveRight = true;
	if (IsLeftBump()) {
		SetLeftBump(false);
	}
}

#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, m_fGravity(1.f)
	, m_fMass(1.f)
	, isPlayer(false)
{

}

CFieldObject::~CFieldObject()
{
}

void CFieldObject::AddGravity()
{
	if (m_bGround)
	{
		m_vVelocity.y = 0;
	}
	else {
		m_vVelocity.y -= m_fGravity * m_fMass *DT;
	}
}

void CFieldObject::tick()
{
	m_vPos = Transform()->GetRelativePos();
	AddGravity();

	m_vPos.x += m_vVelocity.x;
	m_vPos.y += m_vVelocity.y;
	Transform()->SetRelativePos(m_vPos);
}

void CFieldObject::begin()
{

}
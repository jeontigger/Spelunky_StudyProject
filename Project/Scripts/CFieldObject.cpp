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
	m_vPos.y -= m_fGravity * m_fMass;
}

void CFieldObject::tick()
{
	m_vPos = Transform()->GetRelativePos();
	AddGravity();

	Transform()->SetRelativePos(m_vPos);
}

void CFieldObject::begin()
{

}
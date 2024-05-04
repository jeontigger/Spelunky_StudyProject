#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, isPlayer(false)
	, m_bJump(false)
{

}

CFieldObject::~CFieldObject()
{
}

void CFieldObject::AddGravity()
{


}

bool CFieldObject::IsOverlapGround(CGameObject* _pObject)
{
	auto find = std::find(m_Ground.begin(), m_Ground.end(), _pObject);

	if (find == m_Ground.end()) {
		return false;
	}
	else {
		return true;
	}
}

void CFieldObject::AddOverlapGround(CGameObject* _pObject)
{
	m_Ground.push_back(_pObject);
}

void CFieldObject::SubOverlapGround(CGameObject* _pObject)
{
	auto iter = m_Ground.begin();

	for (; iter != m_Ground.end();)
	{
		if (*iter == _pObject)
		{
			iter = m_Ground.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CFieldObject::tick()
{
	m_iGroundCnt = (int)m_Ground.size();
}

#include "CGroundCollider.h"
#include "CWallCollider.h"
#include "CCeilCollider.h"

void CFieldObject::begin()
{
	CScript::begin();

	Vec2 ColliderCenterPos = Collider2D()->GetRelativePos();
	Vec2 ColliderScale = Collider2D()->GetRelativeScale();

	AddScriptParam(SCRIPT_PARAM::INT, "Ground", &m_iGroundCnt);

}

#include "CMovement.h"
void CFieldObject::skill(Vec2 _force)
{
	auto script = GetOwner()->GetScript<CMovement>();
	if (script) {
		script->SetVelocity(Vec3(_force.x, _force.y, 0.f));
	}
}

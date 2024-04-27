#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)

{

}

CFieldObject::~CFieldObject()
{
}

void CFieldObject::AddGravity()
{


}

void CFieldObject::AddOverlapGround(CGameObject* _pObejct)
{
	m_Ground.push_back(_pObejct);
}

void CFieldObject::SubOverlapGround(CGameObject* _pObejct)
{
	auto iter = m_Ground.begin();

	for (; iter != m_Ground.end();)
	{
		if (*iter == _pObejct)
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
	m_iGroundCnt = m_Ground.size();
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

void CFieldObject::skill(Vec2 _force)
{
}

void CFieldObject::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	
}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	
}
#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, m_fGravity(DefaultGravity)
	, m_bUseGravity(true)
	, m_fMass(1.f)
	, isPlayer(false)
	, m_fAirFriction(3.f)
	, m_fGroundFriction(8.f)
	, m_bUseVelocityX(true)
	, m_bUseVelocityY(true)

{

}

CFieldObject::~CFieldObject()
{
}

void CFieldObject::AddGravity()
{
	if (IsGrounded())
	{
		m_vVelocity.y = 0;
	}
	else {
		if(m_bUseGravity)
			m_vVelocity.y -= m_fGravity * m_fMass *DT;
	}


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

	m_vPrevPos = m_vPos;

	m_vPos = Transform()->GetRelativePos();
	AddGravity();

	if(m_bUseVelocityX)
		m_vPos.x += m_vVelocity.x * TileScaleX * DT;
	if(m_bUseVelocityY)
		m_vPos.y += m_vVelocity.y * TileScaleX * DT;

	if (m_vVelocity.x > 0) {
		if (IsGrounded()) {
			m_vVelocity -= m_fGroundFriction * DT;
		}
		else {
			m_vVelocity -= m_fAirFriction * DT;
		}
		if (m_vVelocity.x <= 0) {
			m_vVelocity.x = 0;
		}
	}
	else if (m_vVelocity.x < 0) {
		if (IsGrounded()) {
			m_vVelocity += m_fGroundFriction * DT;
		}
		else {
			m_vVelocity += m_fAirFriction * DT;
		}
		if (m_vVelocity.x >= 0) {
			m_vVelocity.x = 0;
		}
	}
	Transform()->SetRelativePos(m_vPos);

	m_iTileCnt = 0;
	m_bJump = false;
}

#include "CGroundCollider.h"
#include "CWallCollider.h"
#include "CCeilCollider.h"

void CFieldObject::begin()
{
	CScript::begin();

	Vec2 ColliderCenterPos = Collider2D()->GetRelativePos();
	Vec2 ColliderScale = Collider2D()->GetRelativeScale();

}

void CFieldObject::skill(Vec2 _force)
{
	SetVelocity(_force);
}

void CFieldObject::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	
}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	
}
#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, m_fGravity(DefaultGravity)
	, m_fMass(1.f)
	, isPlayer(false)
	, m_bGround(false)
	, m_fAirFriction(3.f)
	, m_fGroundFriction(8.f)

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
		m_vVelocity.y -= m_fGravity * m_fMass *DT;
		m_bGround = 0;
	}

}

void CFieldObject::tick()
{
	m_vPrevPos = m_vPos;

	m_vPos = Transform()->GetRelativePos();
	AddGravity();

	m_vPos.x += m_vVelocity.x * TileScaleX * DT;
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
}

#include "CGroundCollider.h"

void CFieldObject::begin()
{
	CScript::begin();

	Vec2 ColliderCenterPos = Collider2D()->GetRelativePos();
	Vec2 ColliderScale = Collider2D()->GetRelativeScale();

	float ownerZ = Transform()->GetRelativePos().z;

	m_ButtomCollider = new CGroundCollider;
	CGameObject* obj = new CGameObject;
	obj->AddComponent(m_ButtomCollider);
	m_ButtomCollider->Set(GetOwner(), Vec3(ColliderCenterPos.x, ColliderCenterPos.y - ColliderScale.y / 2.f - 1.f, ownerZ), Vec3(ColliderScale.x * 0.95, 1, 1));
	m_ButtomCollider->SetName("GroundCollider");
	GetOwner()->AddChild(obj);
	GamePlayStatic::SpawnGameObject(obj, DetectColliderLayer);

}

void CFieldObject::skill(Vec2 _force)
{
	SetGround(false);
	SetVelocity(_force);
}

#include "CTile.h"

void CFieldObject::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

}
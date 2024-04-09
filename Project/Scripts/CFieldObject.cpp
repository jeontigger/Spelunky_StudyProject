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
#include "CWallCollider.h"
#include "CCeilCollider.h"

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

	m_BackCollider = new CWallCollider;
	obj = new CGameObject;
	obj->AddComponent(m_BackCollider);
	m_BackCollider->Set(GetOwner(), Vec3(ColliderCenterPos.x - ColliderScale.x / 2.f - 1.f, ColliderCenterPos.y, ownerZ), Vec3(0, ColliderScale.y * 0.9, 1));
	GetOwner()->AddChild(obj);
	GamePlayStatic::SpawnGameObject(obj, DetectColliderLayer);

	m_FrontCollider = new CWallCollider;
	obj = new CGameObject;
	obj->AddComponent(m_FrontCollider);
	m_FrontCollider->Set(GetOwner(), Vec3(ColliderCenterPos.x + ColliderScale.x / 2.f + 1.f, ColliderCenterPos.y, ownerZ), Vec3(0, ColliderScale.y * 0.9, 1));
	GetOwner()->AddChild(obj);
	GamePlayStatic::SpawnGameObject(obj, DetectColliderLayer);

	m_TopCollider = new CCeilCollider;
	obj = new CGameObject;
	obj->AddComponent(m_TopCollider);
	m_TopCollider->Set(GetOwner(), Vec3(ColliderCenterPos.x, ColliderCenterPos.y + ColliderScale.y / 2.f + 1.f, ownerZ), Vec3(ColliderScale.x * 0.95, 1, 1));
	GetOwner()->AddChild(obj);
	GamePlayStatic::SpawnGameObject(obj, DetectColliderLayer);
}

void CFieldObject::skill(Vec2 _force)
{
	SetGround(false);
	SetVelocity(_force);
}

#include "CTile.h"
#include "CCharacterScript.h"
#include "CItem.h"

void CFieldObject::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto owner = GetOwner()->GetScript<CItem>();
	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script && owner) {
		if (GetVelocity().Length() > 20.f) {
			auto character = _OtherObj->GetScript<CCharacterScript>();
			if (character) {
				character->Hit(1);
			}
		}
	}
}

void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

}
#include "pch.h"
#include "CCharacterScript.h"

#include "CDetectCollider.h"
#include "CGroundCollider.h"
#include "CWallCollider.h"
#include "CCeilCollider.h"

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

	Vec2 ColliderCenterPos = Collider2D()->GetRelativePos();
	Vec2 ColliderScale = Collider2D()->GetRelativeScale();

	float ownerZ = Transform()->GetRelativePos().z;

	CGameObject* obj;

	m_BackCollider = new CWallCollider;
	obj = new CGameObject;
	obj->AddComponent(m_BackCollider);
	m_BackCollider->Set(GetOwner(), Vec3(ColliderCenterPos.x - ColliderScale.x/2.f - 1.f, ColliderCenterPos.y, ownerZ), Vec3(0, ColliderScale.y * 0.9, 1));
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

#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, m_fGravity(DefaultGravity)
	, m_fMass(1.f)
	, isPlayer(false)
	, m_bGround(false)
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

	if (IsLeftBump()||IsRightBump()) {
		m_vVelocity.x = 0;
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

#include "CTile.h"
void CFieldObject::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
		auto objmat = _Collider->GetColliderWorldMat(); 
		auto tilemat = _OtherCollider->GetColliderWorldMat();

		Vec3 tilePos(tilemat._41, tilemat._42, tilemat._43);
		Vec3 tileScale(tilemat._11, tilemat._22, tilemat._33);
		Vec3 objColPos(objmat._41, objmat._42, objmat._43);
		Vec3 objColScale(objmat._11, objmat._22, objmat._33);

		Vec3 objPos = GetOwner()->Transform()->GetRelativePos();
		Vec2 objVel = GetVelocity();
		Vec3 prevColPos = Vec3(objColPos.x - objVel.x, objColPos.y - objVel.y, objPos.z);

		float deltaY = (prevColPos.y - objColScale.y / 2.f) - (tileScale.y / 2.f + tilePos.y);

		if (deltaY + 1.f > 0) {
			objPos.y = tilePos.y + (tileScale.y + abs(objColScale.y)) / 2.f;
			Transform()->SetRelativePos(objPos);
			SetGround(true);
		}
		else {
			// 오브젝트가 오른쪽
			if (objColPos.x - tilePos.x > 0) {
				objPos.x = tilePos.x + (tileScale.x + abs(objColScale.x))/2.f;
				Transform()->SetRelativePos(objPos);
				SetLeftBump(true);
			}
			else {
				objPos.x = tilePos.x - (tileScale.x + abs(objColScale.x))/2.f;
				Transform()->SetRelativePos(objPos);
				SetRightBump(true);
			}
		}

	}
}

void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
		auto objmat = _Collider->GetColliderWorldMat();
		auto tilemat = _OtherCollider->GetColliderWorldMat();

		Vec3 tilePos(tilemat._41, tilemat._42, tilemat._43);
		Vec3 tileScale(tilemat._11, tilemat._22, tilemat._33);
		Vec3 objColPos(objmat._41, objmat._42, objmat._43);
		Vec3 objColScale(objmat._11, objmat._22, objmat._33);

		Vec3 objPos = GetOwner()->Transform()->GetRelativePos();
		Vec2 objVel = GetVelocity();
		Vec3 prevColPos = Vec3(objColPos.x - objVel.x, objColPos.y - objVel.y, objPos.z);

		float deltaY = (prevColPos.y - objColScale.y / 2.f) - (tileScale.y / 2.f + tilePos.y);

		if (deltaY + 1.f > 0) {
			SetGround(false);
		}
		else {
			//// 오브젝트가 오른쪽
			//if (objColPos.x - tilePos.x > 0) {
			//	objPos.x = tilePos.x + (tileScale.x + abs(objColScale.x)) / 2.f;
			//	Transform()->SetRelativePos(objPos);
			//	SetLeftBump(true);
			//}
			//else {
			//	objPos.x = tilePos.x - (tileScale.x + abs(objColScale.x)) / 2.f;
			//	Transform()->SetRelativePos(objPos);
			//	SetRightBump(true);
			//}
		}

	}
}
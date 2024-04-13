#include "pch.h"
#include "CFieldObject.h"

#include <Engine/CKeyMgr.h>

CFieldObject::CFieldObject(UINT type)
	: CScript(type)
	, m_fGravity(DefaultGravity)
	, m_bUseGravity(true)
	, m_fMass(1.f)
	, isPlayer(false)
	, m_bGround(false)
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
		m_bGround = 0;
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

	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {
		
		// ������ �������� �Ŷ��
		Vec3 vObjPos = Transform()->GetRelativePos();
		Vec3 vel = vObjPos - m_vPrevPos;
		Vec3 vObjColPos = Transform()->GetRelativePos() + Vec3(Collider2D()->GetOffsetPos().x, Collider2D()->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
		Vec3 vObjColScale = _Collider->GetColliderWorldMat().Scale();

		Vec3 vTilePos = _OtherCollider->GetColliderWorldMat().Pos();
		Vec3 vTileScale = _OtherCollider->GetColliderWorldMat().Scale();
			// ���� �÷��ֱ�
		if ((vObjColPos.y - vObjColScale.y / 2.f > vTilePos.y + vTileScale.y / 4.f)) {
			if (vel.y <= 0) {
				// �ö��̴� ��ġ
				Vec3 vColPos = vObjColPos;
				vColPos.y = vTilePos.y + (vTileScale.y + vObjColScale.y) / 2.f;

				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				
				Transform()->SetRelativePos(vPos);

				m_bGround++;
			}
		}		
		// �Ӹ� �ڴ°Ÿ�
		else if (vObjColPos.y + vObjColScale.y / 2.f < vTilePos.y - vTileScale.y / 4.f) {
			if (vel.y >= 0) {
				vel.y = -abs(vel.y);
				SetVelocity(Vec2(vel.x, vel.y));
				Vec3 vColPos = vObjColPos;
				vColPos.y = vTilePos.y - (vTileScale.y + vObjColScale.y) / 2.f;
				Vec3 vPos = vColPos + Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
		// ���� �浹
		else {
			// ������Ʈ�� �����̶��
			if (vObjColPos.x < vTilePos.x) {
				Vec3 vColPos = vObjColPos;

				vColPos.x = vTilePos.x - (vTileScale.x + vObjColScale.x) / 2.f;
				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
			else {
				Vec3 vColPos = vObjColPos;
				vColPos.x = vTilePos.x + (vTileScale.x + abs(vObjColScale.x)) / 2.f;
				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
	}
}

#include "CPlayerScript.h"
void CFieldObject::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {

		Vec3 vObjPos = Transform()->GetRelativePos();
		Vec3 vel = vObjPos - m_vPrevPos;

		Vec3 vObjColPos = Transform()->GetRelativePos() + Vec3(Collider2D()->GetOffsetPos().x, Collider2D()->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
		Vec3 vObjColScale = _Collider->GetColliderWorldMat().Scale();
		Vec3 vTilePos = _OtherCollider->GetColliderWorldMat().Pos();
		Vec3 vTileScale = _OtherCollider->GetColliderWorldMat().Scale();
		// ������ �������ٸ�
		if ((vObjColPos.y - vObjColScale.y / 2.f > vTilePos.y + vTileScale.y / 4.f)) {
			if (vel.y <= 0) {
				Vec3 vColPos = vObjColPos;
				vColPos.y = vTilePos.y + (vTileScale.y + vObjColScale.y) / 2.f;

				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
		// �Ӹ� �ڴ°Ÿ�
		else if (vObjColPos.y + vObjColScale.y / 2.f < vTilePos.y - vTileScale.y / 4.f) {
			if (vel.y >= 0) {
				Vec3 vColPos = vObjColPos;
				vColPos.y = vTilePos.y - (vTileScale.y + vObjColPos.y) / 2.f;
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
		// ������ �ε����ٸ�
		else{
			// ������Ʈ�� �����̶��
			if (vObjColPos.x < vTilePos.x) {
				Vec3 vColPos = vObjColPos;

				vColPos.x = vTilePos.x - (vTileScale.x + vObjColScale.x) / 2.f;
				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
			else {
				Vec3 vColPos = vObjColPos;
				vColPos.x = vTilePos.x + (vTileScale.x + abs(vObjColScale.x)) / 2.f;
				// ĳ���Ϳ� �ö��̴� ��ġ ���� ��� �� ĳ���� ��ġ ����
				Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
	}
}


void CFieldObject::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {
		Vec3 vObjPos = Transform()->GetRelativePos();
		Vec3 vel = vObjPos - m_vPrevPos;

		Vec3 vObjColPos = _Collider->GetColliderWorldMat().Pos();
		Vec3 vObjColScale = _Collider->GetColliderWorldMat().Scale();
		Vec3 vTilePos = _OtherCollider->GetColliderWorldMat().Pos();
		Vec3 vTileScale = _OtherCollider->GetColliderWorldMat().Scale();
	}
}
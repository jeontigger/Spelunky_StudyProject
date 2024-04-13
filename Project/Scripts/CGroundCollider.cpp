#include "pch.h"
#include "CGroundCollider.h"

CGroundCollider::CGroundCollider()
{
}

CGroundCollider::~CGroundCollider()
{
}

#include "CFieldObject.h"
#include "CTile.h"
#include "CItem.h"

void CGroundCollider::tick()
{
}

void CGroundCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CTile>();
	if (script || _OtherObj->GetName() == OutlineWallName) {
		if (script) {
			TileType type = script->GetTileType();
			if (type == TileType::Door || type == TileType::ExitDoor || type == TileType::Ladder || type == TileType::Spike) return;
		}

		auto objmat = _Collider->GetColliderWorldMat();
		auto tilemat = _OtherCollider->GetColliderWorldMat();

		Vec3 ObjColPos = objmat.Pos();
		Vec3 ObjColScale = objmat.Scale();
		Vec3 TileColPos = tilemat.Pos();
		Vec3 TileColScale = tilemat.Scale();

		float objUnderY = ObjColPos.y - ObjColScale.y / 2.f;
		Vec2 vel = m_parent->GetScript<CFieldObject>()->GetVelocity();
		float velY = vel.y;
		float prevObjUnderY = objUnderY - velY * DT;
		float TileTopY = TileColPos.y + TileColScale.y / 2.f;
		float tileJudgeY = TileColPos.y + TileColScale.y / 2.f * 0.5f;
		if (velY < -10.f && m_parent->GetScript<CItem>()) {
			Vec2 vel = m_parent->GetScript<CFieldObject>()->GetVelocity();
			vel.y = abs(vel.y) * 0.5f;
			m_parent->GetScript<CFieldObject>()->SetVelocity(vel);
		}
		else if (velY <= 0 && prevObjUnderY - tileJudgeY > 0) {
			float OwnerY = m_parent->Transform()->GetRelativePos().y;

			Vec3 pos = m_parent->Transform()->GetRelativePos();
			pos.y = TileTopY + OwnerY - objUnderY - 2.f;
			m_parent->Transform()->SetRelativePos(pos);

			m_parent->GetScript<CFieldObject>()->SetGround(true);
		}
	}
}

void CGroundCollider::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::EndOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CTile>();
	if (script || _OtherObj->GetName() == OutlineWallName) {
		if (script) {
			TileType type = script->GetTileType();
			if (type == TileType::Door || type == TileType::ExitDoor || type == TileType::Ladder || type == TileType::Spike) return;
		}
		auto objmat = _Collider->GetColliderWorldMat();
		auto tilemat = _OtherCollider->GetColliderWorldMat();

		Vec3 ObjColPos = objmat.Pos();
		Vec3 ObjColScale = objmat.Scale();
		Vec3 TileColPos = tilemat.Pos();
		Vec3 TileColScale = tilemat.Scale();

		float objUnderY = ObjColPos.y - ObjColScale.y / 2.f;
		float velY = m_parent->GetScript<CFieldObject>()->GetVelocity().y;
		float prevObjUnderY = objUnderY - velY * DT;
		float TileTopY = TileColPos.y + TileColScale.y / 2.f;

		if (velY >= -0.2f) {
			if (!DetectTile()) {
				m_parent->GetScript<CFieldObject>()->ClearGround();
			}
		}
	}
}

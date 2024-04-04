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

void CGroundCollider::tick()
{
}

void CGroundCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
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
		float tileJudgeY = TileColPos.y + TileColScale.y / 2.f * 0.7f;

		if (velY < 0 && prevObjUnderY - tileJudgeY > 0) {
			float OwnerY = m_parent->Transform()->GetRelativePos().y;

			Vec3 pos = m_parent->Transform()->GetRelativePos();
			pos.y = TileTopY + OwnerY - objUnderY;
			m_parent->Transform()->SetRelativePos(pos);

			m_parent->GetScript<CFieldObject>()->SetGround(true);
		}
	}
}

void CGroundCollider::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::EndOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
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

		if (velY >= 0) {
			if (!DetectTile()) {
				m_parent->GetScript<CFieldObject>()->SetGround(false);
			}
		}
	}
}

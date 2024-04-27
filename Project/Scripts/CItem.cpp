#include "pch.h"
#include "CItem.h"

#include "CPlayerScript.h"

void CItem::SetPlayerScript(CPlayerScript* _script)
{
	m_PlayerScript = _script;
}

void CItem::OutPlayerScript()
{
	m_PlayerScript = nullptr;
}

void CItem::PutDown()
{
	Vec3 pos = GetOwner()->Transform()->GetRelativePos();
	if (m_PlayerScript->IsLookRight()) {
		pos.x += 20.f;
	}
	else {
		pos.x -= 20.f;
	}
	GetOwner()->Transform()->SetRelativePos(pos);
	SetVelocity(Vec2(0, 0));
	m_PlayerScript = nullptr;
	m_vPrevPos = pos;
}

void CItem::tick()
{
	CFieldObject::tick();

	if (m_PlayerScript) {
		Vec3 PlayerHandPos = m_PlayerScript->GetItemSocketPos();
		PlayerHandPos.z = HandleZ;
		GetOwner()->Transform()->SetRelativePos(PlayerHandPos);
		
	}
}

#include "CTile.h"

void CItem::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//CFieldObject::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script) {
		if (GetVelocity().Length() > 10.f) {
			auto character = _OtherObj->GetScript<CCharacterScript>();
			if (character) {
				character->Hit(1);
			}
		}
	}

	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {

		TileType type = tile->GetTileType();
		if (type == TileType::Door || type == TileType::Ladder || type == TileType::ExitDoor || type == TileType::Spike) return;

		Vec3 vObjPos = Transform()->GetRelativePos();
		Vec3 vel = vObjPos - m_vPrevPos;
		if (m_vPrevPos == Vec3()) {
			return;
		}
		Vec3 vObjColPos = Transform()->GetRelativePos() + Vec3(Collider2D()->GetOffsetPos().x, Collider2D()->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
		Vec3 vObjColScale = _Collider->GetColliderWorldMat().Scale();

		Vec3 vTilePos = _OtherCollider->GetColliderWorldMat().Pos();
		Vec3 vTileScale = _OtherCollider->GetColliderWorldMat().Scale();
		// 위로 올려주기
		if ((vObjColPos.y - vObjColScale.y / 2.f > vTilePos.y + vTileScale.y / 4.f)) {
			if (vel.y <= 0) {
				if (vel.y < -3.f) {
					vel.y = abs(vel.y) * 0.4f;
					SetVelocity(Vec2(vel.x, vel.y));
				}
				else {
					// 컬라이더 위치
					Vec3 vColPos = vObjColPos;
					vColPos.y = vTilePos.y + (vTileScale.y + vObjColScale.y) / 2.f;

					// 캐릭터와 컬라이더 위치 차이 계산 후 캐릭터 위치 조정
					Vec3 vPos = vColPos - Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();

					Transform()->SetRelativePos(vPos);

				}
				
			}
		}
		// 머리 박는거면
		else if (vObjColPos.y + vObjColScale.y / 2.f < vTilePos.y - vTileScale.y / 4.f) {
			if (type == TileType::Half || type == TileType::LadderHalf) return;
			if (vel.y >= 0) {
				vel.y = -abs(vel.y);
				SetVelocity(Vec2(vel.x, vel.y));
				Vec3 vColPos = vObjColPos;
				vColPos.y = vTilePos.y - (vTileScale.y + vObjColScale.y) / 2.f;
				Vec3 vPos = vColPos + Vec3(_Collider->GetOffsetPos().x, _Collider->GetOffsetPos().y, 0) * Transform()->GetRelativeScale();
				Transform()->SetRelativePos(vPos);
			}
		}
		// 옆에서 부딪힌다면
		else {
			if (type == TileType::Half || type == TileType::LadderHalf) return;
			// 오브젝트가 왼쪽이라면
			if (vObjColPos.x < vTilePos.x) {
				vel.x = -abs(vel.x);
			}
			else {
				vel.x = abs(vel.x);
			}
			SetVelocity(Vec2(vel.x * 0.7, vel.y));
		}
	}

	m_vPrevPos = Transform()->GetRelativePos();
}

void CItem::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObject::Overlap(_Collider, _OtherObj, _OtherCollider);
}


CItem::CItem(UINT type)
	:CFieldObject(type)
{
	SetVelocity(Vec2(0, 0));
}

CItem::~CItem()
{
}

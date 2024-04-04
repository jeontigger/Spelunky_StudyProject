#include "pch.h"
#include "CPlayerHitCollider.h"

CPlayerHitCollider::CPlayerHitCollider()
{
}

CPlayerHitCollider::~CPlayerHitCollider()
{
}

#include "CCharacterScript.h"
#include "CPlayerScript.h"

void CPlayerHitCollider::Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale)
{
	CDetectCollider::Set(parent, vOffsetPos, vOffsetScale);

	GetOwner()->SetName("PlayerHitCollider");
}

void CPlayerHitCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CCharacterScript>();
	if (script) {
		CPlayerScript* playerScript = m_parent->GetScript<CPlayerScript>();
		playerScript->Hit(script->GetDamage());

		Vec3 OwnerPos = m_parent->Transform()->GetRelativePos();
		Vec2 OwnerScale = m_parent->Collider2D()->GetRelativeScale();
		Vec3 TilePos = _OtherObj->Transform()->GetRelativePos();

		auto colmat = _OtherCollider->GetColliderWorldMat();
		Vec3 colpos = colmat.Pos();
		Vec3 colscale = colmat.Scale();
		// 오브젝트가 오른쪽
		if (OwnerPos.x - TilePos.x > 0) {
			playerScript->AddVelocity(Vec2(50.f, 3.f));
			playerScript->SetGround(false);
		}
		else {
			playerScript->AddVelocity(Vec2(-5.f, .5f));
			playerScript->SetGround(false);
		}
	}
}
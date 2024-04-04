#include "pch.h"
#include "CWallCollider.h"

CWallCollider::CWallCollider()
	:CDetectCollider((UINT)SCRIPT_TYPE::WALLCOLLIDER)
{
}

CWallCollider::~CWallCollider()
{
}

#include "CTile.h"
#include "CCharacterScript.h"

void CWallCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
		Vec3 OwnerPos = m_parent->Transform()->GetRelativePos();
		Vec2 OwnerScale = m_parent->Collider2D()->GetRelativeScale();
		Vec3 TilePos = _OtherObj->Transform()->GetRelativePos();

		auto colmat = _OtherCollider->GetColliderWorldMat();
		Vec3 colpos = colmat.Pos();
		Vec3 colscale = colmat.Scale();
		// ������Ʈ�� ������
		if (OwnerPos.x - TilePos.x > 0) {
			OwnerPos.x = colpos.x + colscale.x / 2.f + OwnerScale.x / 2.f;
		}
		else {
			OwnerPos.x = colpos.x - colscale.x / 2.f - OwnerScale.x / 2.f;
		}
		m_parent->Transform()->SetRelativePos(OwnerPos);
		auto objScript = m_parent->GetScript<CCharacterScript>();
		objScript->DontMove();
		Vec2 vel = objScript->GetVelocity();
		vel.x = 0;
		objScript->SetVelocity(vel);
	}
}
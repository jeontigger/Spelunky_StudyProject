#include "pch.h"
#include "CBombExplosion.h"

CBombExplosion::CBombExplosion()
	:CScript((UINT)SCRIPT_TYPE::BOMBEXPLOSION)
	, m_fStartScale(128 * 1.8)
	, m_fIncreaseSpeed(30.f)
	, m_fForce(.1f)
{
}

CBombExplosion::~CBombExplosion()
{
}

void CBombExplosion::begin()
{
	Collider2D()->SetRadius(m_fStartScale);
}

void CBombExplosion::tick()
{
	float radius = Collider2D()->GetRadius();
	radius += m_fIncreaseSpeed * DT;
	Collider2D()->SetRadius(radius);
}

#include "CTile.h"
#include "CFieldObject.h"

void CBombExplosion::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto tile = _OtherObj->GetScript<CTile>();
	if (tile) {
		_OtherCollider->Activate(false);
		GamePlayStatic::DestroyGameObject(_OtherObj);
		return;
	}

	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script) {
		Vec3 otherPos = _OtherCollider->GetColliderWorldMat().Pos();
		Vec3 vPos = _Collider->GetColliderWorldMat().Pos();

		Vec2 vDir;
		vDir.x = otherPos.x - vPos.x;
		vDir.y = otherPos.y - vPos.y;

		float distance = vDir.Length();

		vDir.Normalize();

		Vec2 Force = vDir * m_fForce *  (_Collider->GetRadius() - distance);
		script->SetGround(false);
		script->AddVelocity(Force);
	}
}
#include "pch.h"
#include "CMonsterDetectTileCollider.h"

void CMonsterDetectTileCollider::Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale)
{
	m_parent = parent;
	GetOwner()->SetName(StrMonsterDetectTileColliderName);
	GetOwner()->AddComponent(new CTransform);
	GetOwner()->AddComponent(new CCollider2D);
	Transform()->SetRelativePos(vOffsetPos);
	Transform()->SetRelativeScale(vOffsetScale);
}

CMonsterDetectTileCollider::CMonsterDetectTileCollider()
	: CScript((UINT)SCRIPT_TYPE::MONSTERDETECTTILECOLLIDER)
	, m_iTileCnt(0)
{
}

CMonsterDetectTileCollider::~CMonsterDetectTileCollider()
{
}

#include "CTile.h"
void CMonsterDetectTileCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt++;
	}
}

void CMonsterDetectTileCollider::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt--;
	}
}

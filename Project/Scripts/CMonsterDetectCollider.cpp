#include "pch.h"
#include "CMonsterDetectCollider.h"

void CMonsterDetectCollider::Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale)
{
	m_parent = parent;
	GetOwner()->SetName(StrMonsterDetectColliderName);
	GetOwner()->AddComponent(new CTransform);
	GetOwner()->AddComponent(new CCollider2D);
	Transform()->SetRelativePos(vOffsetPos);
	Transform()->SetRelativeScale(vOffsetScale);
}

CMonsterDetectCollider::CMonsterDetectCollider()
	: CScript((UINT)SCRIPT_TYPE::MONSTERDETECTCOLLIDER)
	, m_iTileCnt(0)
{
}

CMonsterDetectCollider::~CMonsterDetectCollider()
{
}

#include "CTile.h"
#include "CPlayerScript.h"
void CMonsterDetectCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt++;
	}
	else if (_OtherObj->GetScript<CPlayerScript>()) {
		m_iPlayerCnt++;
	}
}

void CMonsterDetectCollider::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt--;
	}
	else if (_OtherObj->GetScript<CPlayerScript>()) {
		m_iPlayerCnt--;
	}
}

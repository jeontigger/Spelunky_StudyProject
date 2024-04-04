#include "pch.h"
#include "CDetectCollider.h"

void CDetectCollider::Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale)
{
	m_parent = parent;
	GetOwner()->SetName(StrMonsterDetectColliderName);
	GetOwner()->AddComponent(new CTransform);
	GetOwner()->AddComponent(new CCollider2D);
	Transform()->SetRelativePos(vOffsetPos);
	Transform()->SetRelativeScale(vOffsetScale);
}

CDetectCollider::CDetectCollider()
	: CScript((UINT)SCRIPT_TYPE::DETECTCOLLIDER)
	, m_iTileCnt(0)
{
}

CDetectCollider::CDetectCollider(UINT _type)
	: CScript((UINT)_type)
{
}

CDetectCollider::~CDetectCollider()
{
}

#include "CTile.h"
#include "CPlayerScript.h"
void CDetectCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt++;
	}
	else if (_OtherObj->GetScript<CPlayerScript>()) {
		m_iPlayerCnt++;
	}
}

void CDetectCollider::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetScript<CTile>()) {
		m_iTileCnt--;
	}
	else if (_OtherObj->GetScript<CPlayerScript>()) {
		m_iPlayerCnt--;
	}
}
#include "pch.h"
#include "CMonsterHitCollider.h"

CMonsterHitCollider::CMonsterHitCollider()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
	, m_parent(nullptr)
{
	
}

CMonsterHitCollider::~CMonsterHitCollider()
{
}

#include "CPlayerScript.h"
#include "CCharacterScript.h"
void CMonsterHitCollider::Set(CGameObject* parent, Vec3 vOffsetPos, Vec3 vOffsetScale)
{
	m_parent = parent;
	GetOwner()->SetName(StrMonsterHitColliderName);
	GetOwner()->AddComponent(new CTransform);
	GetOwner()->AddComponent(new CCollider2D);
	Transform()->SetRelativePos(vOffsetPos);
	Transform()->SetRelativeScale(vOffsetScale);
}
void CMonsterHitCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto script = _OtherObj->GetScript<CPlayerScript>();
	if (script) {
		m_parent->GetScript<CCharacterScript>()->Hit();
	}
}

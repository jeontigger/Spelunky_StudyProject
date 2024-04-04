#include "pch.h"
#include "CMonsterHitCollider.h"

CMonsterHitCollider::CMonsterHitCollider()
	: CDetectCollider((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
{
	
}

CMonsterHitCollider::~CMonsterHitCollider()
{
}

#include "CPlayerScript.h"

void CMonsterHitCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	if (DetectPlayer()) {
		auto script = _OtherObj->GetScript<CPlayerScript>();
		if (script) {
			m_parent->GetScript<CCharacterScript>()->Hit(script->GetDamage());
		}
	}
}

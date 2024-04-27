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
#include "CGroundCollider.h"

void CMonsterHitCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CDetectCollider::BeginOverlap(_Collider, _OtherObj, _OtherCollider);


}

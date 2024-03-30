#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: CFieldObject((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
{
	
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::skill()
{
}

void CPlayerScript::begin()
{
	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
}

void CPlayerScript::tick()
{
	CFieldObject::tick();

}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}
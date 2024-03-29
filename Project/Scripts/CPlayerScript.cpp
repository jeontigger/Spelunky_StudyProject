#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: CScript(PLAYERSCRIPT)
{
	
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{

}

void CPlayerScript::tick()
{

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
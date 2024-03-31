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

#include "CPlayerStartState.h"
void CPlayerScript::begin()
{
	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CPlayerStartState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));
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
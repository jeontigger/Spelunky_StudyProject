#include "pch.h"
#include "CSnakeScript.h"

#include "CSnakeEntryState.h"
#include "CMonsterHitCollider.h"
#include "CMonsterDetectTileCollider.h"

CSnakeScript::CSnakeScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::SNAKESCRIPT)
{
	SetSpeed(2.f);
}

CSnakeScript::~CSnakeScript()
{
}

bool CSnakeScript::DetectFrontTile()
{
	return m_DetectTile->DetectTile();
}

void CSnakeScript::begin()
{
	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CSnakeEntryState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));



	CGameObject* hitcollider = new CGameObject;
	float z = GetOwner()->Transform()->GetRelativePos().z;
	hitcollider->AddComponent(new CMonsterHitCollider);
	hitcollider->GetScript<CMonsterHitCollider>()->Set(GetOwner(), Vec3(0, 0, z), Vec3(60, 20, z));
	GetOwner()->AddChild(hitcollider);
	GamePlayStatic::SpawnGameObject(hitcollider, MonsterColliderLayer);

	CGameObject* detectcollider = new CGameObject;
	z = GetOwner()->Transform()->GetRelativePos().z;
	detectcollider->AddComponent(new CMonsterDetectTileCollider);
	m_DetectTile = detectcollider->GetScript<CMonsterDetectTileCollider>();
	m_DetectTile->Set(GetOwner(), Vec3(-50, -50, z), Vec3(4, 4, z));
	GetOwner()->AddChild(detectcollider);
	GamePlayStatic::SpawnGameObject(detectcollider, MonsterColliderLayer);
}
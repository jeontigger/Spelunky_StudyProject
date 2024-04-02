#include "pch.h"
#include "CSnakeScript.h"

#include "CSnakeEntryState.h"
#include "CMonsterHitCollider.h"
#include "CMonsterDetectCollider.h"

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
	return m_DetectTileCollider->DetectTile();
}

bool CSnakeScript::DetectFrontWall()
{
	return m_DetectWallAndPlayerCollider->DetectTile();
}

bool CSnakeScript::DetectPlayer()
{
	return m_DetectWallAndPlayerCollider->DetectPlayer();
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
	detectcollider->AddComponent(new CMonsterDetectCollider);
	m_DetectTileCollider = detectcollider->GetScript<CMonsterDetectCollider>();
	m_DetectTileCollider->Set(GetOwner(), Vec3(50, -50, z), Vec3(4, 4, z));
	GetOwner()->AddChild(detectcollider);
	GamePlayStatic::SpawnGameObject(detectcollider, MonsterColliderLayer);

	detectcollider = new CGameObject;
	detectcollider->AddComponent(new CMonsterDetectCollider);
	m_DetectWallAndPlayerCollider = detectcollider->GetScript<CMonsterDetectCollider>();
	m_DetectWallAndPlayerCollider->Set(GetOwner(), Vec3(40, -10, z), Vec3(30, 40, z));
	GetOwner()->AddChild(detectcollider);
	GamePlayStatic::SpawnGameObject(detectcollider, MonsterColliderLayer);
}
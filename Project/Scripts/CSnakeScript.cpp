#include "pch.h"
#include "CSnakeScript.h"

#include "CSnakeEntryState.h"
#include "CMonsterHitCollider.h"
#include "CDetectCollider.h"

CSnakeScript::CSnakeScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::SNAKESCRIPT)
{
	SetSpeed(200.f);
	SetHealth(1);
	SetDamage(1);
}

CSnakeScript::CSnakeScript(const CSnakeScript& _origin)
	: CCharacterScript(_origin)
{
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

static int cnt = 0;

void CSnakeScript::begin()
{
	CCharacterScript::begin();

	GetOwner()->SetName("Snake" + to_string(cnt));
	cnt++;

	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CSnakeEntryState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));

	float z = GetOwner()->Transform()->GetRelativePos().z;

	CGameObject* hitcollider = new CGameObject;
	m_HitCollider = new CMonsterHitCollider;
	hitcollider->AddComponent(m_HitCollider);
	m_HitCollider->Set(GetOwner(), Vec3(0, 0, z), Vec3(60, 30, z));
	GetOwner()->AddChild(hitcollider);
	GamePlayStatic::SpawnGameObject(hitcollider, MonsterHitLayer);

	CGameObject* detectcollider = new CGameObject;
	m_DetectTileCollider = new CDetectCollider;
	detectcollider->AddComponent(m_DetectTileCollider);
	m_DetectTileCollider->Set(GetOwner(), Vec3(50, -50, z), Vec3(4, 4, z));
	GetOwner()->AddChild(detectcollider);
	GamePlayStatic::SpawnGameObject(detectcollider, DetectColliderLayer);

	detectcollider = new CGameObject;
	m_DetectWallAndPlayerCollider = new CDetectCollider;
	detectcollider->AddComponent(m_DetectWallAndPlayerCollider);
	m_DetectWallAndPlayerCollider->Set(GetOwner(), Vec3(40, -13, z), Vec3(30, 40, z));
	GetOwner()->AddChild(detectcollider);
	GamePlayStatic::SpawnGameObject(detectcollider, DetectColliderLayer);
}

void CSnakeScript::tick()
{
	CState* state = GetOwner()->StateMachine()->GetFSM()->GetCurState();
	STATE_TYPE type = (STATE_TYPE)state->GetStateType();
	if(type == STATE_TYPE::SNAKEIDLESTATE)
	{
		CCharacterScript::tick();
	}
	else {
		CCharacterScript::tick();
	}
}

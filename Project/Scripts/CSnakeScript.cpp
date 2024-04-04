#include "pch.h"
#include "CSnakeScript.h"

#include "CSnakeEntryState.h"
#include "CMonsterHitCollider.h"
#include "CDetectCollider.h"

CSnakeScript::CSnakeScript()
	: CCharacterScript((UINT)SCRIPT_TYPE::SNAKESCRIPT)
{
	SetSpeed(2.f);
	SetHealth(1);
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
	CCharacterScript::begin();

	GetOwner()->GetScript<CFieldObject>()->ImPlayer();
	auto state = GetOwner()->StateMachine()->GetFSM()->GetState<CSnakeEntryState>();
	GetOwner()->StateMachine()->GetFSM()->ChangeState(CStateMgr::GetStateName(state));

	float z = GetOwner()->Transform()->GetRelativePos().z;

	CGameObject* hitcollider = new CGameObject;
	m_HitCollider = new CMonsterHitCollider;
	hitcollider->AddComponent(m_HitCollider);
	m_HitCollider->Set(GetOwner(), Vec3(0, 0, z), Vec3(60, 20, z));
	GetOwner()->AddChild(hitcollider);
	GamePlayStatic::SpawnGameObject(hitcollider, DetectColliderLayer);

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

	}
}

#include "CPlayerScript.h"

void CSnakeScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CCharacterScript::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CPlayerScript>();
	if (script) {
		script->Hit(GetDamage());
	}
}

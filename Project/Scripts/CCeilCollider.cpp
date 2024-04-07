#include "pch.h"
#include "CCeilCollider.h"

CCeilCollider::CCeilCollider()
	: CDetectCollider((UINT)SCRIPT_TYPE::CEILCOLLIDER)
{
}

CCeilCollider::~CCeilCollider()
{
}

#include "CCharacterScript.h"
#include "CTile.h"

void CCeilCollider::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto script = _OtherObj->GetScript<CTile>();
	if (script) {
		TileType type = script->GetTileType();
		if (type == TileType::Door || type == TileType::Ladder || type == TileType::LadderHalf || type == TileType::Half || type == TileType::Spike) return;
		
		CCharacterScript* script = m_parent->GetScript<CCharacterScript>();
		Vec2 vel = script->GetVelocity();
		vel.y = -(abs(vel.y));
		script->SetVelocity(vel);
	}
}

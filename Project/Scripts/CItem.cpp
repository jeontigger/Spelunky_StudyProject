#include "pch.h"
#include "CItem.h"

#include "CPlayerScript.h"

void CItem::SetPlayerScript(CPlayerScript* _script)
{
	m_PlayerScript = _script;
}

void CItem::OutPlayerScript()
{
	m_PlayerScript = nullptr;
}

void CItem::PutDown()
{
	Vec3 pos = GetOwner()->Transform()->GetRelativePos();
	if (m_PlayerScript->IsLookRight()) {
		pos.x += 20.f;
	}
	else {
		pos.x -= 20.f;
	}
	GetOwner()->Transform()->SetRelativePos(pos);
	//SetVelocity(Vec2(0, 0));
	m_PlayerScript = nullptr;
	//m_vPrevPos = pos;
}

void CItem::tick()
{
	CFieldObject::tick();

	if (m_PlayerScript) {
		Vec3 PlayerHandPos = m_PlayerScript->GetItemSocketPos();
		PlayerHandPos.z = HandleZ;
		GetOwner()->Transform()->SetRelativePos(PlayerHandPos);
		
	}
}

#include "CTile.h"

void CItem::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CItem::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObject::Overlap(_Collider, _OtherObj, _OtherCollider);
}


CItem::CItem(UINT type)
	:CFieldObject(type)
{
}

CItem::~CItem()
{
}

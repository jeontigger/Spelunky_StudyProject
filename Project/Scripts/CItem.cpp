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
	SetVelocity(Vec2(0, 0));
	m_PlayerScript = nullptr;

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

void CItem::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CFieldObject::BeginOverlap(_Collider, _OtherObj, _OtherCollider);

	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script) {
		if (GetVelocity().Length() > 10.f) {
			auto character = _OtherObj->GetScript<CCharacterScript>();
			if (character) {
				character->Hit(1);
			}
		}
	}
}


CItem::CItem(UINT type)
	:CFieldObject(type)
{
	SetVelocity(Vec2(0, 0));
}

CItem::~CItem()
{
}

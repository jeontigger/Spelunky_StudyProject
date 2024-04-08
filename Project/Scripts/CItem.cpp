#include "pch.h"
#include "CItem.h"

#include "CPlayerScript.h"

void CItem::SetPlayerScript(CPlayerScript* _script)
{
	m_PlayerScript = _script;
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

CItem::CItem(UINT type)
	:CFieldObject(type)
{
}

CItem::~CItem()
{
}

#include "pch.h"
#include "CExitDoor.h"

CExitDoor::CExitDoor()
	: CScript((UINT)SCRIPT_TYPE::EXITDOOR)
{
}

CExitDoor::~CExitDoor()
{
}

void CExitDoor::begin()
{
	m_KeyTex = CAssetMgr::GetInst()->Load<CPrefab>(ButtonIconPrefKey, ButtonIconPrefKey)->Instantiate();
	m_KeyTex->Animator2D()->Play(AnimButtonIcon);

	Vec3 vPos = GetOwner()->Transform()->GetRelativePos();
	vPos.z = PlayerZ + 20;
	vPos.y += 100.f;
	m_KeyTex->Transform()->SetRelativePos(vPos);
	GamePlayStatic::SpawnGameObject(m_KeyTex, TileLayer);

	m_KeyTex->Collider2D()->Activate(false);
}

void CExitDoor::tick()
{
}

#include "CPlayerScript.h"

void CExitDoor::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto player = _OtherObj->GetScript<CPlayerScript>();
	if (player) {
		m_KeyTex->Collider2D()->Activate(true);
	}
}

void CExitDoor::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto player = _OtherObj->GetScript<CPlayerScript>();
	if (player) {
		m_KeyTex->Collider2D()->Activate(false);
	}
}

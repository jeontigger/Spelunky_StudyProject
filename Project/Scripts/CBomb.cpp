#include "pch.h"
#include "CBomb.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CPlayerScript.h"
#include "CCameraMovement.h"
#include "CStage.h"
#include "CAnimationLoop.h"


CBomb::CBomb()
	: CItem((UINT)SCRIPT_TYPE::BOMB)
	, m_fBombTimer(4.f)
	, m_fScaleTime(1.f)
	, m_fScaleReduceSpeed(40.f)
	, m_fAnimationChangeStart(1.f)
	, m_fAnimationChangeTime(0.3f)
{
}

CBomb::~CBomb()
{
}

void CBomb::Bomb()
{
	GamePlayStatic::DestroyGameObject(GetOwner());
	((CStage*)CLevelMgr::GetInst()->GetCurrentLevel())->GetMainCamera()->GetScript<CCameraMovement>()->Shake(0.3, 20);
	CGameObject* obj = CAnimationLoop::Instantiate();
	obj->Transform()->SetRelativePos(Transform()->GetRelativePos());
	obj->GetScript<CAnimationLoop>()->Set({ wstring(AnimBombExplosion)});
	obj->Transform()->SetRelativeScale(Vec3(128 * 3, 128 * 3, 0));
	obj->Collider2D()->SetColliderType(COLLIDER2D_TYPE::CIRCLE);
	obj->Collider2D()->SetRadius(128 * 1.8);
	GamePlayStatic::SpawnGameObject(obj, ItemLayer);
}

void CBomb::tick()
{
	CItem::tick();

	m_fBombTimer -= DT;
	m_fScaleTimer -= DT;

	Vec3 vScale = GetOwner()->Transform()->GetRelativeScale();
	vScale.x -= m_fScaleReduceSpeed * DT;
	vScale.y -= m_fScaleReduceSpeed * DT;
	GetOwner()->Transform()->SetRelativeScale(vScale);

	if (m_fScaleTimer < 0) {
		m_fScaleTimer = m_fScaleTime;
		GetOwner()->Transform()->SetRelativeScale(m_vOriginScale*1.2);
	}

	if (m_fBombTimer < 0 && !GetOwner()->IsDead()) {
		Bomb();
	}

	if (m_fAnimationChangeStart < 0) {
		if (m_fAnimationChangeTimer < 0) {
			if (m_iAnimationCnt == 0) {
				Animator2D()->Play(AnimBombBlack);
			}
			else if (m_iAnimationCnt == 1) {
				Animator2D()->Play(AnimBombRed);
			}
			else {
				Animator2D()->Play(AnimBombYellow);
				m_fAnimationChangeTime *= 0.7f;
			}
			m_iAnimationCnt++;
			m_iAnimationCnt %= 3;
			m_fAnimationChangeTimer = m_fAnimationChangeTime;
		}
		
		m_fAnimationChangeTimer -= DT;

	}
	m_fAnimationChangeStart -= DT;
}

void CBomb::begin()
{
	CItem::begin();

	m_fScaleTimer = m_fScaleTime;
	m_fAnimationChangeTimer = m_fAnimationChangeTime;
	m_vOriginScale = GetOwner()->Transform()->GetRelativeScale();
	Animator2D()->Play(AnimBombBlack);
	m_iAnimationCnt = 2;
}

void CBomb::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (!_OtherObj->GetScript<CPlayerScript>()) {
		CItem::BeginOverlap(_Collider, _OtherObj, _OtherCollider);
	}
}

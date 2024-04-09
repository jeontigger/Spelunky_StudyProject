#include "pch.h"
#include "CBomb.h"

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

	if (m_fBombTimer < 0) {
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
#include "pch.h"
#include "CWhip.h"

CWhip::CWhip()
	: CScript((UINT)SCRIPT_TYPE::WHIP)
{
}

CWhip::~CWhip()
{
}

void CWhip::Attack()
{
	Collider2D()->Activate(true);
	Animator2D()->Play(AnimWhip, false);
}

void CWhip::tick()
{
	if (Animator2D()->GetCurAnim()) {
		if(Animator2D()->GetCurAnim()->IsFinish())
			Collider2D()->Activate(false);
	}
}

void CWhip::begin()
{
	Collider2D()->Activate(false);
}

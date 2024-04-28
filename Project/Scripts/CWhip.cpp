#include "pch.h"
#include "CWhip.h"

#include "CPlayerScript.h"

CWhip::CWhip()
	: CScript((UINT)SCRIPT_TYPE::WHIP)
{
	m_pSound = CAssetMgr::GetInst()->Load<CSound>(Sndwhip02a, Sndwhip02a);
}

CWhip::~CWhip()
{
}

void CWhip::Attack()
{
	Collider2D()->Activate(true);
	Animator2D()->Play(AnimWhip, false);
	m_pSound->Play(1);

	Transform()->SetRelativePos(Vec3(-60, 48, WhipBackZ));
	Collider2D()->SetOffsetScale(Vec2(0.8f, 0.8f));
}

void CWhip::tick()
{
	if (Animator2D()->GetCurAnim()) {
		if(Animator2D()->GetCurAnim()->IsFinish())
			Collider2D()->Activate(false);
	}


	CAnim* anim = Animator2D()->GetCurAnim();

	if (!anim) return;
	if (anim->IsFinish()) return;

	int idx = anim->GetIdx();
	int positive = 1;
	if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
		positive = 1;
	}
	else {
		positive = -1;
	}

	if (idx == 0) {
		Transform()->SetRelativePos(Vec3(-60.f, 48.f, (float)positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 1) {
		Transform()->SetRelativePos(Vec3(-60, 28, (float)positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 2) {
		Transform()->SetRelativePos(Vec3(-60, 28, (float)positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 3) {
		Transform()->SetRelativePos(Vec3(0, 20, (float)positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 4) {
		Transform()->SetRelativePos(Vec3(75, -25, (float)positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.2f));
	}
}

void CWhip::begin()
{
	Collider2D()->Activate(false);
}

#include "CFieldObject.h"
#include "CPlayerScript.h"

void CWhip::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script) {
		if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
			//script->AddVelocity(Vec2(3.f, 3.f));
		}
		else if (!GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
			//script->AddVelocity(Vec2(-3.f, 3.f));
		}

		auto monster = _OtherObj->GetScript<CCharacterScript>();
		if (monster) {
			monster->Hit(1);
		}
	}
}

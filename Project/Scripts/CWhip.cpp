#include "pch.h"
#include "CWhip.h"

#include "CPlayerScript.h"

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
	int positive = 1.f;
	if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
		positive = 1.f;
	}
	else {
		positive = -1.f;
	}

	if (idx == 0) {
		Transform()->SetRelativePos(Vec3(-60, 48, positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 1) {
		Transform()->SetRelativePos(Vec3(-60, 28, positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 2) {
		Transform()->SetRelativePos(Vec3(-60, 28, positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 3) {
		Transform()->SetRelativePos(Vec3(0, 20, positive * WhipBackZ));
		Collider2D()->SetOffsetScale(Vec2(0.8f, 0.4f));
	}
	else if (idx == 4) {
		Transform()->SetRelativePos(Vec3(75, -25, positive * WhipBackZ));
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
		script->ClearGround();
		if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
			script->AddVelocity(Vec2(3.f, 3.f));
		}
		else if (!GetOwner()->GetParent()->GetScript<CPlayerScript>()->IsLookRight()) {
			script->AddVelocity(Vec2(-3.f, 3.f));
		}

		auto monster = _OtherObj->GetScript<CCharacterScript>();
		if (monster) {
			monster->Hit(1);
		}
	}
}

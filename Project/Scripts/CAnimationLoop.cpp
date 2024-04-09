#include "pch.h"
#include "CAnimationLoop.h"

#include <Engine/CAnim.h>

CAnimationLoop::CAnimationLoop()
	: CScript((UINT)SCRIPT_TYPE::ANIMATIONLOOP)
{
}

CAnimationLoop::~CAnimationLoop()
{
}

void CAnimationLoop::PlayFront()
{
	wstring animName = m_listWait.front();

	if (!Animator2D()->FindAnim(animName)) {
		wstring path = CPathMgr::GetContentPath() + animName;

		ifstream fin(path);
		if (!fin.is_open()) {
			MessageBox(nullptr, L"경로 오류!", L"애니메이션 추가", 0);
			return;
		}
		CAnim* anim = new CAnim;
		anim->LoadFromFile(fin);
		anim->SetName(animName);
		Animator2D()->AddAnim(anim);
	}
	Animator2D()->Play(animName);
}

void CAnimationLoop::Set(const wstring& _animName, int _loopCnt)
{
	for (int i = 0; i < _loopCnt; i++) {
		m_listWait.push_back(_animName);
	}
}

void CAnimationLoop::begin()
{
	PlayFront();
}

void CAnimationLoop::tick()
{
	if (m_listWait.size() == 0 && Animator2D()->GetCurAnim()->IsFinish()) {
		GamePlayStatic::DestroyGameObject(GetOwner());
	}

	if (Animator2D()->GetCurAnim()->IsFinish()) {
		PlayFront();
	}
}


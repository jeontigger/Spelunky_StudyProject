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
	Animator2D()->Play(animName, false);

	m_listWait.pop_front();
}

void CAnimationLoop::Set(const wstring& _animName, int _loopCnt)
{
	for (int i = 0; i < _loopCnt; i++) {
		m_listWait.push_back(_animName);
	}
}

CGameObject* CAnimationLoop::Instantiate()
{
	CGameObject* obj = new CGameObject;
	obj->AddComponent(new CTransform);
	obj->AddComponent(new CCollider2D);
	obj->AddComponent(new CAnimator2D);
	obj->AddComponent(new CMeshRender);
	obj->AddComponent(new CAnimationLoop);
	obj->SetName(L"AnimationLoopObject");

	obj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	obj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	return obj;
}

void CAnimationLoop::begin()
{
	PlayFront();
}

void CAnimationLoop::tick()
{
	if (Animator2D()->GetCurAnim()->IsFinish()) {
		if (m_listWait.size() == 0) {
			GamePlayStatic::DestroyGameObject(GetOwner());
		}
		else {
			PlayFront();
		}
	}
}


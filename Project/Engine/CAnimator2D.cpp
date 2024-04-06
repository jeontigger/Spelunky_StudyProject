#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
{

}

CAnimator2D::CAnimator2D(const CAnimator2D& _OriginAnimator)
	: CComponent(_OriginAnimator)
	, m_CurAnim(nullptr)
	, m_bRepeat(_OriginAnimator.m_bRepeat)
{
	map<wstring, CAnim*>::const_iterator iter = _OriginAnimator.m_mapAnim.begin();
	for (; iter != _OriginAnimator.m_mapAnim.end(); ++iter)
	{
		CAnim* pCloneAnim = iter->second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(iter->first, pCloneAnim));
	}

	if (nullptr != _OriginAnimator.m_CurAnim)
	{
		m_CurAnim = FindAnim(_OriginAnimator.m_CurAnim->GetName());
	}
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);	
}

void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
		return;

	if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}
	m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{	
	CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop
	, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS)
{
	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);

	pAnim = new CAnim;	
	pAnim->Create(this, _AltasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::AddAnim(const wstring& _strKey, Ptr<CTexture> _AltasTex, const vector<tAnimFrm>& frms)
{
	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);

	pAnim = new CAnim;
	pAnim->Create(this, _AltasTex, frms);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::AddAnim(CAnim* anim)
{
	CAnim* pAnim = FindAnim(anim->GetName());
	if (pAnim) {
		MessageBox(nullptr, L"이미 있는 애니메이션입니다", L"애니메이션 추가", 0);
		return;
	}
	anim->m_Animator = this;
	m_mapAnim.insert(make_pair(anim->GetName(), anim));
}

float CAnimator2D::GetAnimDuration(CAnim* anim)
{
	float duration = 0.f;
	for (int i = 0; i < anim->m_vecFrm.size(); i++) {
		duration += anim->m_vecFrm[i].Duration;
	}

	return duration;
}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

CAnim* CAnimator2D::FindAnim(const string& _strAnimName)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(ToWString(_strAnimName));

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}

void CAnimator2D::SaveToFile(FILE* _File)
{
	// 애니메이션 개수 저장
	size_t AnimCount = m_mapAnim.size();
	fwrite(&AnimCount, sizeof(size_t), 1, _File);

	for (const auto& pair : m_mapAnim)
	{
		pair.second->SaveToFile(_File);
	}
	
	// 플레이 중이던 애니메이션의 키를 저장한다.
	wstring PlayAnimName;

	if (nullptr != m_CurAnim)
	{
		PlayAnimName = m_CurAnim->GetName();
	}

	SaveWString(PlayAnimName, _File);
	fwrite(&m_bRepeat, sizeof(bool), 1, _File);
}

void CAnimator2D::SaveToFile(ofstream& fout)
{
	fout << m_mapAnim.size() << endl;

	for (const auto& pair : m_mapAnim)
	{
		pair.second->SaveToFile(fout);
	}
}

void CAnimator2D::LoadFromFile(FILE* _File)
{
	// 애니메이션 개수 로드
	size_t AnimCount = 0;
	fread(&AnimCount, sizeof(size_t), 1, _File);
		
	for (size_t i = 0; i < AnimCount; ++i)
	{
		CAnim* pAnim = new CAnim;
		pAnim->LoadFromFile(_File);

		pAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));		
	}
}

void CAnimator2D::LoadFromFile(ifstream& fin)
{
	int cnt;
	fin >> cnt;

	for (int i = 0; i < cnt; i++) {
		CAnim* anim = new CAnim;
		anim->LoadFromFile(fin);

		anim->m_Animator = this;
		m_mapAnim.insert(make_pair(anim->GetName(), anim));
	}
}

#include "pch.h"
#include "CParticleOnce.h"
CParticleOnce::CParticleOnce()
	: CScript((UINT)SCRIPT_TYPE::PARTICLEONCE)
	, m_fDeleteTime(0.5f)
{
}

CParticleOnce::~CParticleOnce()
{
}

CGameObject* CParticleOnce::Instantiate(const wstring& _prefKey, const wstring& _atlasKey)
{
	CGameObject* obj = CAssetMgr::GetInst()->Load<CPrefab>(_prefKey, _prefKey)->Instantiate();
	obj->ParticleSystem()->SetParticleTex(_atlasKey);
	return obj;
}

void CParticleOnce::tick()
{
	if (!m_bInfinite) {
		if (m_acctime>m_fDeleteTime) {
			GamePlayStatic::DestroyGameObject(GetOwner());
		}
	}

	m_acctime += DT;
}

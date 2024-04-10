#include "pch.h"
#include "CParticleOnce.h"
CParticleOnce::CParticleOnce()
	: CScript((UINT)SCRIPT_TYPE::PARTICLEONCE)
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
	//if (m_acctime > 0.5f) {
	//	GamePlayStatic::DestroyGameObject(GetOwner());
	//}

	m_acctime += DT;
}

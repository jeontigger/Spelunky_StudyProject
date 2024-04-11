#include "pch.h"
#include "CTitleLevel.h"

#include <Engine\CRenderMgr.h>
#include <Engine\CLayer.h>
#include <Engine\CCollisionMgr.h>
#include <Engine/CKeyMgr.h>

#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CCamera.h>
#include <Engine\CCollider2D.h>
#include <Engine\CLight2D.h>

#include "CCameraMovement.h"
#include "CBlink.h"
#include "CParticleOnce.h"


void CTitleLevel::tick()
{
	CLevel::tick();

	if (m_State == TitleLevelState::AnyKeyPress) {
		if (CKeyMgr::GetInst()->AnyKeyPressed()) {
			ChangeLevelState(TitleLevelState::Select);
		}
	}
	else if(m_State==TitleLevelState::Select){
		if (KEY_TAP(ESC)) {
			ChangeLevelState(TitleLevelState::AnyKeyPress);
		}
	}
}

void CTitleLevel::begin()
{
	CLevel::begin();

	CCollisionMgr::GetInst()->LayerCheck(CameraLayer, BackgroundLayer);
	
	CRenderMgr::GetInst()->SetDebugPosition(false);
}

CTitleLevel::CTitleLevel()
	:m_State(TitleLevelState::AnyKeyPress)
{
	m_arrLayer[1]->SetName(L"Background");
	m_arrLayer[5]->SetName(L"Light");

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	AddObject(pLight, L"Light");

	//Main Camera Object 생성
	m_MainCamera = new CGameObject;
	m_MainCamera->SetName(L"MainCamera");
	m_MainCamera->AddComponent(new CTransform);
	m_MainCamera->AddComponent(new CCamera);
	m_MainCamera->AddComponent(new CCollider2D);
	m_MainCamera->AddComponent(new CCameraMovement);
	m_MainCamera->Camera()->SetScale(CameraNormalScale);


	m_MainCamera->Transform()->SetRelativePos(Vec3(0, 0, 0));
	m_MainCamera->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	m_MainCamera->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	m_MainCamera->Collider2D()->SetOffsetScale(Vec2(TileBlockScaleX * 1.5 + 5, TileBlockScaleY + TileScaleY));

	m_MainCamera->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	m_MainCamera->Camera()->SetCameraPriority(0);
	m_MainCamera->Camera()->LayerCheckAll();
	m_MainCamera->Camera()->LayerCheck(31, false);

	AddObject(m_MainCamera, CameraLayer);

	CGameObject* obj = CAssetMgr::GetInst()->Load<CPrefab>(TitleBackgroundPrefKey, TitleBackgroundPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimTitleBackground);
	AddObject(obj, BackgroundLayer);

	obj = CAssetMgr::GetInst()->Load<CPrefab>(TitleGirlPrefKey, TitleGirlPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimTitleGirl);
	AddObject(obj, BackgroundLayer);

	obj = CAssetMgr::GetInst()->Load<CPrefab>(TitleAnyKey, TitleAnyKey)->Instantiate();
	obj->Animator2D()->Play(AnimTitleAnyKey);
	obj->GetScript<CBlink>()->Set(1, 0.3f);
	AddObject(obj, BackgroundLayer);

	obj = CAssetMgr::GetInst()->Load<CPrefab>(TitleFire, TitleFire)->Instantiate();
	obj->GetScript<CParticleOnce>()->Infinite(true);
	obj->ParticleSystem()->SetParticleTex(TexParticleSmallAtlas);
	AddObject(obj, BackgroundLayer);
}

CTitleLevel::~CTitleLevel()
{
}

void CTitleLevel::ChangeLevelState(TitleLevelState _state)
{
	m_State = _state;
	switch (_state)
	{
	case TitleLevelState::AnyKeyPress:

		break;
	case TitleLevelState::Select:

		break;
	default:
		break;
	}
}

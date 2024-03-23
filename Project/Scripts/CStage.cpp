#include "pch.h"
#include "CStage.h"


#include <Engine/CKeyMgr.h>
#include <Engine/CFontMgr.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CLevelMgr.h>

#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Engine/CLayer.h>

#include "CRandomMgr.h"

#include "CBackgroundScript.h"

CStage::CStage()
	: m_state(StageState::NONE)
	, m_SP(nullptr)
{
	m_arrLayer[0]->SetName(L"Default");
	m_arrLayer[1]->SetName(L"Background");
	m_arrLayer[2]->SetName(L"Tile");
	m_arrLayer[3]->SetName(L"Player");
	m_arrLayer[4]->SetName(L"Monster");
	m_arrLayer[5]->SetName(L"Light");
	m_arrLayer[6]->SetName(L"Tile");
	m_arrLayer[31]->SetName(L"UI");

	// 傈开 堡盔 眠啊
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	AddObject(pLight, L"Light");

	CGameObject* pObj = nullptr;

	// Player Object 积己
	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);

	pObj->Transform()->SetRelativePos(Vec3(-9000.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	AddObject(pObj, L"Player", false);

	 //Main Camera Object 积己
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f,0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(31, false);

	AddObject(pCamObj, 0);


	CLevelMgr::GetInst()->ChangeLevel(this, LEVEL_STATE::PLAY);
}

CStage::~CStage()
{
}

void CStage::ChangeState(StageState _state)
{
	m_state = _state;

	switch (_state)
	{
	case StageState::NONE:
		break;
	case StageState::CREATE_BLOCK:
		CreateBlocks();
		break;

	case StageState::CREATE_ENTRANCE:
		CreateEntrance();
		break;

	case StageState::CREATE_EXIT:
		CreateExit();
		break;

	case StageState::GENERATE_PATH:
		GeneratePath();
		break;

	case StageState::ATTACH_TILEBLOCK:
		break;
	case StageState::TILE_INSTANCING:
		break;
	case StageState::END:
		break;
	default:
		break;
	}
}

void CStage::CreateBlocks()
{

	Font data = {};
	data._fPosX = 30.f;
	data._fPosY = 20.f;
	data._fFontSize = 32;
	data._Color = FONT_RGBA(255, 30, 30, 255);
	CFontMgr::GetInst()->DrawFont(L"CreateTileBlocks", data, 1.f);

	CGameObject* pObj ;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			pObj = new CGameObject;
			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->Transform()->SetRelativeScale(TileBlockScaleVec);

			pObj->Transform()->SetRelativePos(Vec3(col * TileBlockScaleX - TileBlockScaleX * 1.5, -row * TileBlockScaleY + TileBlockScaleY * 1.5, 0));
			wstring name = L"DummyBlock" + std::to_wstring(row * 4 + col);
			pObj->SetName(name);


			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(MapGenBlockMtrl));
			pObj->MtrlSetScalar(INT_0, StageState::CREATE_BLOCK);
			m_vecBlocks.push_back(pObj);
			GamePlayStatic::SpawnGameObject(pObj, 7);
		}
	}
}

void CStage::CreateEntrance()
{
	UINT32 seed = 1337108209;
	CRandomMgr::GetInst()->GenNewSeed(seed);

	int num;
	num = GETRANDOM(10);
	num = GETRANDOM(10);
	num = GETRANDOM(10);
	num = GETRANDOM(10);
}

void CStage::CreateExit()
{
}

void CStage::GeneratePath()
{
	Font data = {};
	data._fPosX = 30.f;
	data._fPosY = 20.f;
	data._fFontSize = 32;
	data._Color = FONT_RGBA(255, 30, 30, 255);
	CFontMgr::GetInst()->DrawFont(L"GeneratePath", data, 1.f);

	for (auto obj : m_vecBlocks) {
		obj->MtrlSetScalar(INT_0, StageState::GENERATE_PATH);
	}
}

void CStage::tick()
{
	CLevel::tick();



}

void CStage::finaltick()
{
	CLevel::finaltick();

	if (m_state == StageState::NONE) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::CREATE_BLOCK);
		}
	}else if(m_state == StageState::CREATE_BLOCK) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::CREATE_ENTRANCE);
		}
	}


	
}

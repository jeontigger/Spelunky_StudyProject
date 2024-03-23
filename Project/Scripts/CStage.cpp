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

	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.8f, 0.8f, 0.8f));
	AddObject(pLight, L"Light");

	CGameObject* pObj = nullptr;

	// Player Object 생성
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

	 //Main Camera Object 생성
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

	case StageState::SELECT_ENTRANCE:
		SelectEntrance();
		break;

	case StageState::SELECT_EXIT:
		SelectExit();
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

	PrintChangeState(L"Create Blocks");

	CGameObject* pObj;
	for (int row = 0; row < STAGETILEROW; row++) {
		m_vecBlocks.push_back({});
		for (int col = 0; col < STAGETILECOL; col++) {
			pObj = new CGameObject;
			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->Transform()->SetRelativeScale(TileBlockScaleVec);

			pObj->Transform()->SetRelativePos(Vec3(col * TileBlockScaleX - TileBlockScaleX * (STAGETILEROW/2 - 0.5), -row * TileBlockScaleY + TileBlockScaleY * (STAGETILECOL/2 - 0.5), 0));
			wstring name = L"DummyBlock" + std::to_wstring(row * 4 + col);
			pObj->SetName(name);


			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(MapGenBlockMtrl));
			pObj->MtrlSetScalar(INT_0, StageState::CREATE_BLOCK);
			m_vecBlocks[row].push_back(pObj);
			GamePlayStatic::SpawnGameObject(pObj, 7);
		}
	}
}

void CStage::SelectEntrance()
{
	PrintChangeState(L"Select Entrance");

	m_iEntracnePos = GETRANDOM(STAGETILECOL);
	m_vecBlocks[0][m_iEntracnePos]->DMtrlSetScalar(INT_0, 2);

}

void CStage::SelectExit()
{
	PrintChangeState(L"Select Exit");
	m_iExitPos = GETRANDOM(STAGETILECOL);
	m_vecBlocks[STAGETILEROW - 1][m_iExitPos]->DMtrlSetScalar(INT_0, 2);
}

void CStage::GeneratePath()
{
	PrintChangeState(L"Generate Path");

	for (int row = 0; row < STAGETILEROW; row++)
	{
		for (int col = 0; col < STAGETILECOL; col++)
		{
			m_visited[row][col] = false;
		}
	}



	Vec2 curPos(m_iEntracnePos, 0);
	Vec2 targetPos(m_iExitPos, STAGETILEROW - 1);

	m_visited[0][m_iEntracnePos] = true;

	vector<Vec2> path;
	path.push_back(curPos);

	DFSGenerate(path, false);

}

int arrRow[] = { 0, 1, 0 };
int arrCol[] = { 1, 0, -1 };

void CStage::DFSGenerate(vector<Vec2>& _path, bool find)
{
	Vec2 curPos = _path.back();
	if (find || curPos.x == m_iExitPos && curPos.y == STAGETILEROW - 1) {
		m_Path = _path;
		find = true;
		return;
	}

	bool check[] = { false, false, false };
	while (true) {
		int ran;
		while (true) {
			// 좌, 우, 하 중에 가능한걸 골라
			ran = GETRANDOM(3);
			if (!check[ran]) {
				check[ran] = true;
				break;
			}
		}
		
		Vec2 nextPos(curPos.x + arrCol[ran], curPos.y + arrRow[ran]);

		if (0 <= nextPos.x && nextPos.x < STAGETILECOL && 0 <= nextPos.y && nextPos.y < STAGETILEROW){
			if (!m_visited[(int)nextPos.y][(int)nextPos.x]) {
				m_visited[(int)nextPos.y][(int)nextPos.x] = true;
				_path.push_back(nextPos);
				DFSGenerate(_path, find);
				_path.pop_back();
				m_visited[(int)nextPos.y][(int)nextPos.x] = false;
			}
		}

		bool allcheck = true;
		for (size_t i = 0; i < 3; i++)
		{
			if (!check[i]) {
				allcheck = false;
				break;
			}
		}

		if (allcheck)
		{
			break;
		}
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
			ChangeState(StageState::SELECT_ENTRANCE);
		}
	}else if (m_state == StageState::SELECT_ENTRANCE) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::SELECT_EXIT);
		}
	}else if (m_state == StageState::SELECT_EXIT) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::GENERATE_PATH);
		}
	}else if (m_state == StageState::GENERATE_PATH) {
		PathVisualization();
	}


	
}

void CStage::PrintChangeState(const wchar_t* _content)
{
	Font data = {};
	data._fPosX = 30.f;
	data._fPosY = 20.f;
	data._fFontSize = 32;
	data._Color = FONT_RGBA(255, 30, 30, 255);
	CFontMgr::GetInst()->DrawFont(_content, data, 1.f);
}

void CStage::PathVisualization()
{
	static float acc = 0.f;
	float duration = 0.1f;

	static int i = 1;

	if (i >= m_Path.size() - 1) {
		ChangeState(StageState::ATTACH_TILEBLOCK);
		return;
	}

	acc += DT;
	if (acc > duration) {
		auto pos = m_Path[i];
		m_vecBlocks[(int)pos.y][(int)pos.x]->DMtrlSetScalar(INT_0, 3);
		acc = 0.f;
		i++;
	}
	
}

#include "pch.h"
#include "CStage.h"


#include <Engine/CKeyMgr.h>
#include <Engine/CFontMgr.h>
#include <Engine/CTimeMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CCollisionMgr.h>

#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Engine/CLayer.h>

#include "CRandomMgr.h"
#include "CCameraMovement.h"
#include "CStagePack.h"
#include "CTile.h"

CStage::CStage()
	: m_state(StageState::NONE)
	, m_SP(nullptr)
{
	m_arrLayer[0]->SetName(L"Default");
	m_arrLayer[1]->SetName(L"Background");
	m_arrLayer[2]->SetName(L"Tile");
	m_arrLayer[3]->SetName(L"Player");
	m_arrLayer[4]->SetName(L"CameraCollider");
	m_arrLayer[5]->SetName(L"Light");
	m_arrLayer[6]->SetName(L"Camera");
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
	pCamObj->AddComponent(new CCollider2D);
	pCamObj->AddComponent(new CCameraMovement);
	

	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f,0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeScale(Vec3(TileBlockScaleX*2, TileBlockScaleY + TileScaleY, 0.f));

	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(31, false);

	AddObject(pCamObj, L"Camera");

	//Main Camera Block 생성
	pCamObj = new CGameObject;
	pCamObj->SetName(CameraColliderWallName);
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCollider2D);

	pCamObj->Transform()->SetRelativePos(Vec3(-TileBlockScaleX *2 - TileScaleX*3 , 0.f, 0.f));
	pCamObj->Transform()->SetRelativeScale(Vec3(TileScaleX * 2, TileBlockScaleY * 4, 1.f));
	AddObject(pCamObj, L"CameraCollider");

	pCamObj = pCamObj->Clone();
	pCamObj->Transform()->SetRelativePos(Vec3(TileBlockScaleX * 2 + TileScaleX * 3, 0.f, 0.f));
	AddObject(pCamObj, L"CameraCollider");

	pCamObj = new CGameObject;
	pCamObj->SetName(CameraColliderPlatformName);
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCollider2D);

	pCamObj->Transform()->SetRelativePos(Vec3(0.f, -TileBlockScaleY * 2 - TileScaleY * 3, 0.f));
	pCamObj->Transform()->SetRelativeScale(Vec3(TileBlockScaleX * 4, TileScaleY * 2, 1.f));

	AddObject(pCamObj, L"CameraCollider");

	pCamObj = pCamObj->Clone();
	pCamObj->Transform()->SetRelativePos(Vec3(0.f, TileBlockScaleY * 2 + TileScaleY * 3, 0.f));
	AddObject(pCamObj, L"CameraCollider");

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
		FitType();
		break;

	case StageState::ATTACH_TILEBLOCK:
		SelectBlock();
		break;

	case StageState::REGIST_BACKGROUND:
		RegistBackground();
		break;

	case StageState::TILE_INSTANCING:
		TileInstancing();
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
		m_vecBackgrounds.push_back({});
		for (int col = 0; col < STAGETILECOL; col++) {
			pObj = new CGameObject;
			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->AddComponent(new CCollider2D);

			pObj->Transform()->SetRelativeScale(TileBlockScaleVec);

			pObj->Transform()->SetRelativePos(Vec3(col * TileBlockScaleX - TileBlockScaleX * (STAGETILEROW/2 - 0.5), -row * TileBlockScaleY + TileBlockScaleY * (STAGETILECOL/2 - 0.5), BackgroundZ));
			wstring name = L"DummyBlock" + std::to_wstring(row * 4 + col);
			pObj->SetName(name);


			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(MapGenBlockMtrl));
			pObj->MtrlSetScalar(INT_0, StageState::CREATE_BLOCK);
			m_vecBackgrounds[row].push_back(pObj);
			GamePlayStatic::SpawnGameObject(pObj, 7);
		}
	}
}

void CStage::SelectEntrance()
{
	PrintChangeState(L"Select Entrance");

	m_iEntrancePos = GETRANDOM(STAGETILECOL);
	m_vecBackgrounds[0][m_iEntrancePos]->DMtrlSetScalar(INT_0, 2);

}

void CStage::SelectExit()
{
	PrintChangeState(L"Select Exit");
	m_iExitPos = GETRANDOM(STAGETILECOL);
	m_vecBackgrounds[STAGETILEROW-1][m_iExitPos]->DMtrlSetScalar(INT_0, 2);
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
	Vec2 curPos(m_iEntrancePos , 0);
	Vec2 targetPos(m_iExitPos , STAGETILEROW - 1);

	m_visited[0][m_iEntrancePos] = true;

	vector<Vec2> path;
	path.push_back(curPos);

	DFSGenerate(path, false);

}

int arrRow[] = { 0, 1, 0 };
int arrCol[] = { 1, 0, -1 };

void CStage::DFSGenerate(vector<Vec2>& _path, bool find)
{
	Vec2 curPos = _path.back();
	if (find || curPos.x == m_iExitPos&& curPos.y == STAGETILEROW - 1) {
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

void CStage::FitType()
{
	for (int row = 0; row < STAGETILEROW; row++) {
		for (int col = 0; col < STAGETILECOL; col++)
		{
			m_arrTileBlocks[row][col].SetBlockType(TileBlockType::Side);
		}
	}


	m_arrTileBlocks[0][m_iEntrancePos].SetBlockType(TileBlockType::Entrance);
	if (m_Path[1].y == 1) {
		m_arrTileBlocks[0][m_iEntrancePos].SetBlockType(TileBlockType::Entrance_Fall);
	}

	Vec2 prevPos(m_iEntrancePos, 0);
	for (int i = 1; i < m_Path.size() - 1; i++) {
		Vec2 curPos = m_Path[i];
		Vec2 nextPos = m_Path[i + 1];

		// 떨어지는거라면 
		if (prevPos.y == curPos.y - 1) {
			// 다음에도 떨어지는지
			if (nextPos.y== curPos.y+1) {
				m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Fall_Drop);
			}
			else {
				m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Drop);
			}
		}
		// 옆에서 온거라면
		else if (prevPos.y == curPos.y) {
			// 다음에 떨어지는지
			if (nextPos.y == curPos.y + 1) {
				m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Fall);
			}
			else {
				m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Normal);
			}
		}
		prevPos = curPos;
	}

	Vec2 curPos = m_Path.back();
	// 떨어진거라면
	if (prevPos.y == curPos.y - 1) {
		m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Exit_Drop);
	}
	else {
		m_arrTileBlocks[(int)curPos.y][(int)curPos.x].SetBlockType(TileBlockType::Exit);
	}
}

void CStage::SelectBlock()
{
	PrintChangeState(L"SelectBlock");
	for (int row = 0; row < STAGETILEROW; row++)
	{
		for (int col = 0; col < STAGETILECOL; col++)
		{
			m_arrTileBlocks[row][col] = m_SP->GetRandomBlock(m_arrTileBlocks[row][col].GetBlockType());
		}
	}
}

void CStage::RegistBackground()
{
	PrintChangeState(L"RegistBG");
	auto bg = m_SP->GetBackground();

	for (int row = 0; row < STAGETILEROW; row++)
	{
		for (int col = 0; col < STAGETILECOL; col++)
		{
			m_vecBackgrounds[row][col]->DMtrlSetTex(TEX_0, bg);
		}
	}
}

void CStage::TileInstancing()
{
	for (int row = 0; row < STAGETILEROW; row++)
	{
		for (int col = 0; col < STAGETILECOL; col++)
		{
			int colpos = 0 - TileBlockScaleX * (STAGETILECOL / 2) + TileBlockScaleX / 2 + TileBlockScaleX * col;
			int rowpos = 0 + TileBlockScaleY * (STAGETILEROW / 2) - TileBlockScaleY / 2 - TileBlockScaleY * row;
			m_arrTileBlocks[row][col].TileInstancing(rowpos, colpos);
		}
	}

	Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(OutlineWallKey, OutlineWallKey);
	Ptr<CTexture> tex = CAssetMgr::GetInst()->Load<CTexture>(OutlineAtlasPath, OutlineAtlasPath);

	int maxcount = 7;
	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		Vec3 scale = object->Transform()->GetRelativeScale();
		object->Transform()->SetRelativePos(Vec3(TileBlockScaleX * 2 + TileScaleX, -(maxcount / 2) * scale.y + scale.y * j, OutlineWallZ));
		GamePlayStatic::SpawnGameObject(object, TileLayer);
	}
	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		Vec3 scale = object->Transform()->GetRelativeScale();
		object->Transform()->SetRelativePos(Vec3(-(TileBlockScaleX * 2 + TileScaleX), -(maxcount / 2) * scale.y + scale.y * j, OutlineWallZ));
		GamePlayStatic::SpawnGameObject(object, TileLayer);
	}

	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		Vec3 scale = object->Transform()->GetRelativeScale();
		Vec3 rotation = object->Transform()->GetRelativeRotation();
		object->Transform()->SetRelativePos(Vec3(-(maxcount / 2) * scale.y + scale.y * j, TileBlockScaleY * 2 + TileScaleY, OutlineWallZ));
		rotation.z = XM_PI/2;
		object->Transform()->SetRelativeRotation(rotation);
		GamePlayStatic::SpawnGameObject(object, TileLayer);
	}

	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		Vec3 scale = object->Transform()->GetRelativeScale();
		Vec3 rotation = object->Transform()->GetRelativeRotation();
		object->Transform()->SetRelativePos(Vec3(-(maxcount / 2) * scale.y + scale.y * j, -(TileBlockScaleY * 2 + TileScaleY), OutlineWallZ));
		rotation.z = XM_PI / 2;
		object->Transform()->SetRelativeRotation(rotation);
		GamePlayStatic::SpawnGameObject(object, TileLayer);
	}
}

void CStage::tick()
{
	CLevel::tick();
}

void CStage::finaltick()
{
	CLevel::finaltick();


	if (m_State == LEVEL_STATE::STOP)
		return;

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
	else if (m_state == StageState::ATTACH_TILEBLOCK) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::REGIST_BACKGROUND);
		}
	}
	else if (m_state == StageState::REGIST_BACKGROUND) {
		if (KEY_TAP(LBTN)) {
			ChangeState(StageState::TILE_INSTANCING);
		}
	}
}

void CStage::begin()
{
	CLevel::begin();

	CCollisionMgr::GetInst()->LayerCheck(L"Camera", L"CameraCollider");
	CCollisionMgr::GetInst()->LayerCheck(L"Tile", L"Camera");
	CCollisionMgr::GetInst()->LayerCheck(7, 6);
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
		m_vecBackgrounds[(int)pos.y][(int)pos.x]->DMtrlSetScalar(INT_0, 3);
		acc = 0.f;
		i++;
	}
	
}

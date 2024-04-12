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
#include "CTileMgr.h"

#include "CCameraMovement.h"
#include "CStagePack.h"
#include "CTile.h"
#include "CUI.h"

bool test = true;

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

	 //Main Camera Object 생성
	m_MainCamera = new CGameObject;
	m_MainCamera->SetName(L"MainCamera");
	m_MainCamera->AddComponent(new CTransform);
	m_MainCamera->AddComponent(new CCamera);
	m_MainCamera->AddComponent(new CCollider2D);
	m_MainCamera->AddComponent(new CCameraMovement);
	

	m_MainCamera->Transform()->SetRelativePos(Vec3(TileBlockScaleX * 2.f, -TileBlockScaleY * 2.f, 0.f));
	m_MainCamera->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	m_MainCamera->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	m_MainCamera->Collider2D()->SetOffsetScale(Vec2(TileBlockScaleX * 1.5, TileBlockScaleY + TileScaleY));

	m_MainCamera->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	m_MainCamera->Camera()->SetCameraPriority(0);
	m_MainCamera->Camera()->LayerCheckAll();
	m_MainCamera->Camera()->LayerCheck(31, false);

	AddObject(m_MainCamera, L"Camera");

	m_UICamera = new CGameObject;
	m_UICamera->SetName(L"UICamera");
	m_UICamera->AddComponent(new CTransform);
	m_UICamera->AddComponent(new CCamera);
	m_UICamera->Camera()->SetScale(CameraNormalScale);

	m_UICamera->Transform()->SetRelativePos(Vec3(0.5f, 9000.f, 0.f));
	m_UICamera->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

	m_UICamera->Camera()->SetCameraPriority(1);
	m_UICamera->Camera()->LayerCheck(31, true);
	AddObject(m_UICamera, 0);

	//Main Camera Block 생성
	pObj = new CGameObject;
	pObj->SetName(CameraColliderWallName);
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);

	pObj->Transform()->SetRelativePos(Vec3(TileBlockScaleX * STAGETILECOL + TileScaleX * 3 , - TileBlockScaleY * STAGETILEROW / 2.f, 0.f));
	pObj->Transform()->SetRelativeScale(Vec3(TileScaleX * 2, TileBlockScaleY * 4, 1.f));
	AddObject(pObj, L"CameraCollider");

	pObj = pObj->Clone();
	pObj->Transform()->SetRelativePos(Vec3(-TileScaleX * 3, -TileBlockScaleY * STAGETILEROW / 2.f, 0.f));
	AddObject(pObj, L"CameraCollider");

	pObj = new CGameObject;
	pObj->SetName(CameraColliderPlatformName);
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);

	pObj->Transform()->SetRelativePos(Vec3(TileBlockScaleX * STAGETILECOL / 2.f, TileScaleY * 3, 0.f));
	pObj->Transform()->SetRelativeScale(Vec3(TileBlockScaleX * 4, TileScaleY * 2, 1.f));
	AddObject(pObj, L"CameraCollider");

	pObj = pObj->Clone();
	pObj->Transform()->SetRelativePos(Vec3(TileBlockScaleX * STAGETILECOL / 2.f, -(TileBlockScaleY * STAGETILEROW + TileScaleY * 3), 0.f));
	AddObject(pObj, L"CameraCollider");

	if (test) {
		Ptr<CPrefab> prefab;
		CGameObject* obj;

		prefab = CAssetMgr::GetInst()->Load<CPrefab>(OutlineWallKey, OutlineWallKey);

		obj = prefab->Instantiate();
		obj->SetName(OutlineWallName);
		obj->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f, -TileBlockScaleY / 2.f - TileScaleY, OutlineWallZ));
		AddObject(obj, OutlinerLayer);

		//prefab = CAssetMgr::GetInst()->Load<CPrefab>(SnakePrefKey, SnakePrefKey);
		//obj = prefab->Instantiate();
		//obj->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f - TileScaleX, -TileBlockScaleY / 2.f - TileScaleY, MonsterZ));
		//AddObject(obj, MonsterLayer);

		prefab = CAssetMgr::GetInst()->Load<CPrefab>(RockPrefKey, RockPrefKey);
		obj = prefab->Instantiate();
		obj->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f, -TileBlockScaleY / 2.f - TileScaleY, ItemZ));
		AddObject(obj, ItemLayer);

		prefab = CAssetMgr::GetInst()->Load<CPrefab>(PlayerPrefKey, PlayerPrefKey);
		m_Player = prefab->Instantiate();
		m_Player->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f, -TileBlockScaleY / 2.f - TileScaleY, PlayerZ));
		AddObject(m_Player, PlayerLayer);

		m_MainCamera->Camera()->SetScale(CameraNormalScale);

		m_MainCamera->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f, -TileBlockScaleY / 2.f, 0.f));


		prefab = CAssetMgr::GetInst()->Load<CPrefab>(ParticleBloodPrefKey, ParticleBloodPrefKey);
		obj = prefab->Instantiate();
		obj->Transform()->SetRelativePos(Vec3(TileBlockScaleX / 2.f, -TileBlockScaleY / 2.f - TileScaleY* 2, TileZ+10));
		obj->ParticleSystem()->SetParticleTex(TexParticleSmallAtlas);
		AddObject(obj, PlayerLayer);

		//PauseMenuInit();
	}
	CTileMgr::GetInst()->Init();
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

	case StageState::MONSTER_GENERATING:
		MonsterGenerating();
		break;

	case StageState::ITEM_GENERATING:
		ItemGenerating();
		break;

	case StageState::PLAYER_SETTING:
		PlayerSetting();
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

			pObj->Transform()->SetRelativePos(Vec3((col + 0.5f) * TileBlockScaleX, -(row + 0.5f)* TileBlockScaleY, BackgroundZ));
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
			m_arrTileBlocks[row][col].TileInstancing(row, col);
		}
	}

	
	Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(OutlineWallKey, OutlineWallKey);

	int maxcount = 6;
	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		object->SetName(OutlineWallName);
		Vec3 scale = object->Transform()->GetRelativeScale();
		object->Transform()->SetRelativePos(Vec3(TileBlockScaleX * STAGETILECOL + TileScaleX, -(0.25f + j) * scale.y, OutlineWallZ));
		GamePlayStatic::SpawnGameObject(object, OutlinerLayer);
	}
	for (int j = 0; j < maxcount; j++) {
		CGameObject* object = prefab->Instantiate();
		object->SetName(OutlineWallName);
		Vec3 scale = object->Transform()->GetRelativeScale();
		object->Transform()->SetRelativePos(Vec3(-TileScaleX, -(0.25f + j) * scale.y, OutlineWallZ));
		GamePlayStatic::SpawnGameObject(object, OutlinerLayer);
	}

	for (int j = 0; j < maxcount+1; j++) {
		CGameObject* object = prefab->Instantiate();
		object->SetName(OutlineWallName);
		Vec3 scale = object->Transform()->GetRelativeScale();
		Vec3 rotation = object->Transform()->GetRelativeRotation();
		object->Transform()->SetRelativePos(Vec3((0.25f + j) * scale.y, TileScaleY, OutlineWallZ));
		rotation.z = XM_PI/2;
		object->Transform()->SetRelativeRotation(rotation);
		GamePlayStatic::SpawnGameObject(object, OutlinerLayer);
	}

	for (int j = 0; j < maxcount+1; j++) {
		CGameObject* object = prefab->Instantiate();
		object->SetName(OutlineWallName);
		Vec3 scale = object->Transform()->GetRelativeScale();
		Vec3 rotation = object->Transform()->GetRelativeRotation();
		object->Transform()->SetRelativePos(Vec3((0.25f + j) * scale.y, -(TileBlockScaleY * STAGETILEROW + TileScaleY), OutlineWallZ));
		rotation.z = XM_PI / 2;
		object->Transform()->SetRelativeRotation(rotation);
		GamePlayStatic::SpawnGameObject(object, OutlinerLayer);
	}
}

void CStage::MonsterGenerating()
{
	PrintChangeState(L"Monster Generating");

	for (int row = 0; row < STAGETILEROW; row++) {
		for (int col = 0; col < STAGETILECOL; col++) {
			m_arrTileBlocks[row][col].MonsterGenerating(row, col);
		}
	}
}

void CStage::ItemGenerating()
{
	PrintChangeState(L"Item Generating");

	for (int row = 0; row < STAGETILEROW; row++) {
		for (int col = 0; col < STAGETILECOL; col++) {
			m_arrTileBlocks[row][col].ItemGenerating(row, col);
		}
	}
}

void CStage::PlayerSetting()
{
	auto prefab = CAssetMgr::GetInst()->Load<CPrefab>(PlayerPrefKey, PlayerPrefKey);
	m_Player = prefab->Instantiate();
	Vec3 vPos = CTileMgr::GetInst()->GetEntrancePos();
	vPos.z = PlayerZ;
	m_Player->Transform()->SetRelativePos(vPos);
	GamePlayStatic::SpawnGameObject(m_Player, PlayerLayer);
	vPos.z = 0.f;
	m_MainCamera->Transform()->SetRelativePos(vPos);
	m_MainCamera->Camera()->SetScale(CameraNormalScale);
	m_MainCamera->GetScript<CCameraMovement>()->SetTarget(m_Player);
}

void CStage::tick()
{
	CLevel::tick();
}

#include <Engine/CFontMgr.h>
void CStage::finaltick()
{
	CLevel::finaltick();

	CTileMgr::GetInst()->tick();

	if (KEY_TAP(ESC)) {
		if (m_State == LEVEL_STATE::PAUSE) {
			CLevelMgr::GetInst()->GetCurrentLevel()->ChangeState(LEVEL_STATE::PLAY);
		}
		else if(m_State == LEVEL_STATE::PLAY){
			CLevelMgr::GetInst()->GetCurrentLevel()->ChangeState(LEVEL_STATE::PAUSE);
			m_iCursorIdx = 0;
		}
	}


	if (KEY_TAP(Y)) {
		Vec2 mousepos = CKeyMgr::GetInst()->GetMousePos();
		m_Player->Transform()->SetRelativePos(Vec3(mousepos.x, mousepos.y, PlayerZ));

		int a = 0;

	}

	PauseMenuControl();

	if (test)
		return;

	if (m_State == LEVEL_STATE::STOP)
		return;

	if (m_state == StageState::NONE) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::CREATE_BLOCK);
		}
	}else if(m_state == StageState::CREATE_BLOCK) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::SELECT_ENTRANCE);
		}
	}else if (m_state == StageState::SELECT_ENTRANCE) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::SELECT_EXIT);
		}
	}else if (m_state == StageState::SELECT_EXIT) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::GENERATE_PATH);
		}
	}else if (m_state == StageState::GENERATE_PATH) {
		PathVisualization();
	}
	else if (m_state == StageState::ATTACH_TILEBLOCK) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::REGIST_BACKGROUND);
		}
	}
	else if (m_state == StageState::REGIST_BACKGROUND) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::TILE_INSTANCING);
		}
	}
	else if (m_state == StageState::TILE_INSTANCING) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::MONSTER_GENERATING);
		}
	}
	else if (m_state == StageState::MONSTER_GENERATING) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::ITEM_GENERATING);
		}
	}
	else if (m_state == StageState::ITEM_GENERATING) {
		if (KEY_TAP(RBTN)) {
			ChangeState(StageState::PLAYER_SETTING);
		}
	}

}

#include "CTileMgr.h"

void CStage::begin()
{
	CLevel::begin();

	CCollisionMgr::GetInst()->LayerCheck(L"Camera", L"CameraCollider");
	CCollisionMgr::GetInst()->LayerCheck(L"Tile", L"Camera");
	CCollisionMgr::GetInst()->LayerCheck(PlayerAttackLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerLayer, MonsterLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerLayer, ItemLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerLayer, MonsterHitLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerLayer, DetectColliderLayer);
	CCollisionMgr::GetInst()->LayerCheck(OutlinerLayer, DetectColliderLayer);
	CCollisionMgr::GetInst()->LayerCheck(MonsterHitLayer, DetectColliderLayer);
	CCollisionMgr::GetInst()->LayerCheck(MonsterLayer, PlayerHitLayer);
	CCollisionMgr::GetInst()->LayerCheck(MonsterLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(OutlinerLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(ItemLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(TileAroundLayer, CameraLayer);
	CCollisionMgr::GetInst()->LayerCheck(ItemLayer, MonsterLayer);
	CCollisionMgr::GetInst()->LayerCheck(7, 6);

	CCollisionMgr::GetInst()->LayerCheck(PlayerAttackLayer, MonsterLayer);
	CCollisionMgr::GetInst()->LayerCheck(PlayerAttackLayer, ItemLayer);
	CCollisionMgr::GetInst()->LayerCheck(ItemLayer, ItemLayer);


	CTileMgr::GetInst()->CheckLayer(DetectColliderLayer);
	CTileMgr::GetInst()->CheckLayer(ItemLayer);
	CTileMgr::GetInst()->CheckLayer(PlayerLayer);

	if (test) {
		m_arrTileBlocks[0][0].SetBlockType(TileBlockType::Exit);
		m_arrTileBlocks[0][0] = m_SP->GetBlock(TileBlockType::Exit, 0);
		m_arrTileBlocks[0][0].TileInstancing(0, 0);
		m_MainCamera->GetScript<CCameraMovement>()->SetTarget(m_Player);
	}
	PauseMenuInit();
}

void CStage::PrintChangeState(const wchar_t* _content)
{
	Font data = {};
	data._fPosX = 30.f;
	data._fPosY = 50.f;
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
		acc = 0.f;
		i = 1;
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

void CStage::PauseMenuInit()
{
	CGameObject* obj;
	m_vecPauseMenu.resize((UINT)PAUSEMENU::END);

	// 돌 생성
	obj = CAssetMgr::GetInst()->Load<CPrefab>(PauseRockPrefKey, PauseRockPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimPauseRock);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(960, PauseBoardHide + MenuOffsets[0]));
	AddObject(obj, UILayer);
	m_vecPauseMenu[(UINT)PAUSEMENU::ROCK] = obj;

	// 현수막 생성
	obj = CAssetMgr::GetInst()->Load<CPrefab>(PauseHeaderPrefKey, PauseHeaderPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimPauseHeader);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(960, PauseBoardHide + MenuOffsets[1]));
	AddObject(obj, UILayer);
	m_vecPauseMenu[(UINT)PAUSEMENU::HEADER] = obj;

	// 커서 생성
	obj = CAssetMgr::GetInst()->Load<CPrefab>(PauseMenuCursorPrefKey, PauseMenuCursorPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimPauseCursor);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(960, PauseBoardHide + MenuOffsets[2]));
	AddObject(obj, UILayer);
	m_vecPauseMenu[(UINT)PAUSEMENU::CURSOR] = obj;

	// 메뉴 보드 생성
	obj = CAssetMgr::GetInst()->Load<CPrefab>(PauseMenuBoardPrefKey, PauseMenuBoardPrefKey)->Instantiate();
	obj->Animator2D()->Play(AnimPauseMenuBoard);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(960, PauseBoardHide));
	AddObject(obj, UILayer);
	m_vecPauseMenu[(UINT)PAUSEMENU::BOARD] = obj;

}

void CStage::PauseMenuControl()
{
	for (int i = 0; i < m_vecPauseMenu.size(); i++) {

		Vec2 vPos = m_vecPauseMenu[i]->GetScript<CUI>()->GetScreenPos();
		Vec2 vTarget = vPos;

		int movepos;
		if (m_State == LEVEL_STATE::PAUSE) {
			movepos = PauseBoardOpen;
		}
		else {
			movepos = PauseBoardHide;
		}

		if (i == (UINT)PAUSEMENU::CURSOR) {
			vTarget.y = movepos + MenuOffsets[i] + PauseCursorSpace * m_iCursorIdx;
		}
		else {
			vTarget.y = movepos + MenuOffsets[i];
		}

		Vec2 vDir = vTarget - vPos;
		float fDistance = vDir.Length();
		vDir.Normalize();

		vPos += vDir * 4000.f * DT_ENGINE;

		if (fDistance > 1.f) {
			m_vecPauseMenu[i]->GetScript<CUI>()->SetScreenPos(vPos);
		}
	}

	if (m_State == LEVEL_STATE::PAUSE) {
		if (KEY_TAP(UP)) {
			m_iCursorIdx--;
		}
		if (KEY_TAP(DOWN)) {
			m_iCursorIdx++;
		}
		m_iCursorIdx += (UINT)MENUTYPE::END;
		m_iCursorIdx %= (UINT)MENUTYPE::END;

		if (KEY_TAP(ENTER)) {
			switch ((MENUTYPE)m_iCursorIdx)
			{
			case MENUTYPE::CONTINUE:
				CLevelMgr::GetInst()->GetCurrentLevel()->ChangeState(LEVEL_STATE::PLAY);
				break;
			case MENUTYPE::STOP:

				break;
			case MENUTYPE::QUIT:
				PostQuitMessage(0);
				break;
			case MENUTYPE::END:
				break;
			default:
				break;
			}
		}
	}
}

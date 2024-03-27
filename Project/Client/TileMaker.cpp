#include "pch.h"
#include "TileMaker.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CPathMgr.h>

#include <Scripts/CStagePack.h>
#include <Scripts/CTileBlock.h>

TileMaker::TileMaker()
	: UI("TileMaker", UITileMakerName)
	, m_curStage(nullptr)
	, m_state(TileMakerState::NONE)
	, m_iTypeCursor(-1)
	, m_iStageIdx(0)
	, m_iBGIdx(0)
{
	wstring blocktilepath = L"texture\\tilemap\\blocktile.png";
	m_texBlockTile = ASSET_LOAD(CTexture, blocktilepath);

	m_curStage = m_newStage = new CStagePack;

	Utils::LoadAllPath("texture\\Background", m_vecBackgroundPaths);
	for (auto path : m_vecBackgroundPaths) {
		m_vecBackgrounds.push_back(ASSET_LOAD(CTexture, ToWString(path)));
	}
	int a = 0;
}

TileMaker::~TileMaker()
{
	if (m_newStage)
		delete m_newStage;

	Delete_Vec(m_vecStages);
}

void TileMaker::render_update()
{
	if (m_state == TileMakerState::NONE) {
		if (ImGui::Button("Make New Stage")) {
			ChangeState(TileMakerState::New);
		}
		if (ImGui::Button("Stage Modify")) {
			ChangeState(TileMakerState::Modify);
		}
	}


	// 스테이지 생성
	if (m_state == TileMakerState::New) {
		ImGui::BeginChild("LeftTops", ImVec2(320, 800), true, 0);
		ReturnButton();
		ImGui::SameLine();
		NewStageSaveButton();

		ButtonTitle("Stage Name");
		ImGui::InputText("##stagename", m_StageName, 32);

		SelectBackground();

		TileBlockMenu(m_vecTileBlocks);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockMaps", ImVec2(200, 800), true, 0);
		PrintStageBlocks(m_vecTileBlocks);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockTiles", ImVec2(1000,800), true, 0);
		PrintTileBlock(m_curTileBlock);
		ImGui::EndChild();
		
	}

	// 기존 스테이지 변경
	if (m_state == TileMakerState::Modify) {
		ImGui::BeginChild("LeftTops", ImVec2(320, 800), true, 0);
		ReturnButton();
		ImGui::SameLine();
		if (ImGui::Button("Stage Save")) {
			MessageBox(nullptr, L"스테이지가 저장되었습니다", L"타일메이커", MB_OK);

			SaveStage(m_curStage, m_vecTileBlocks, m_iStageIdx);
			ClearTileBlocks(m_vecTileBlocks);

			ChangeState(TileMakerState::NONE);
		}

		ButtonTitle("Select Stage");

		int prev = m_iStageIdx;
		VecCombo("##tilemaker1", m_StageNames, m_iStageIdx);
		if (prev != m_iStageIdx) {
			SortTileBlocks(m_vecStages[m_iStageIdx]);
			m_iBGIdx = Utils::StringToEnum(m_vecBackgroundPaths, ToString(m_vecStages[m_iStageIdx]->GetBackground()->GetKey()));
			m_curTileBlock = m_newTileBlock;
			m_curBlockName = NewBlockName;
		}

		SelectBackground();

		TileBlockMenu(m_vecTileBlocks);

		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockMaps", ImVec2(200, 800), true, 0);
		PrintStageBlocks(m_vecTileBlocks);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockTiles", ImVec2(1000, 800), true, 0);
		PrintTileBlock(m_curTileBlock);
		ImGui::EndChild();
	}
}

void TileMaker::ChangeState(TileMakerState _state)
{
	m_iTypeCursor = -1;
	m_state = _state;
	ClearTileBlocks(m_vecTileBlocks);
	m_curBlockName = NewBlockName;
	m_curTileBlock = m_newTileBlock;
	switch (_state)
	{
	case TileMakerState::NONE:
		break;
	case TileMakerState::New:

		if (m_newStage) delete m_newStage;
		m_curStage = m_newStage = new CStagePack;
		for (int i = 0; i < 32; i++) {
			m_StageName[i] = 0;
		}
		m_iBGIdx = 0;

		break;

	case TileMakerState::Modify:
		m_StageNames.clear();
		Utils::LoadAllPath("stage", m_StageNames);
		LoadAllStages();
		SortTileBlocks(m_vecStages[0]);
		m_iBGIdx = Utils::StringToEnum(m_vecBackgroundPaths, ToString(m_vecStages[0]->GetBackground()->GetKey()));
		m_iStageIdx = 0;
		break;

	case TileMakerState::END:
		break;
	default:
		break;
	}
}

void TileMaker::ReturnButton()
{
	if (ImGui::Button("Return")) {
		m_state = TileMakerState::NONE;
	}
}

void TileMaker::NewStageSaveButton()
{
	if (ImGui::Button("Stage Save")) {
		if (m_StageName[0] == 0) {
			MessageBox(nullptr, L"스테이지 이름을 지정해주세요", L"타일메이커", MB_OK);
		}
		else {
			MessageBox(nullptr, L"스테이지가 저장되었습니다", L"타일메이커", MB_OK);

			SaveStage(m_newStage, m_vecTileBlocks);

			if (m_newStage) delete m_newStage;
			m_curStage = m_newStage = new CStagePack;

			m_state = TileMakerState::NONE;
		}
	}
}

void TileMaker::LoadAllStages()
{
	Delete_Vec(m_vecStages);
	m_vecStages.clear();

	for (int i = 0; i < m_StageNames.size(); i++) {
		string path = ToString(CPathMgr::GetContentPath());
		path += m_StageNames[i];

		CStagePack* stage = new CStagePack;
		ifstream fin;
		fin.open(path.c_str());
		if (fin.is_open()) {
			fin >> (*stage);
			m_vecStages.push_back(stage);
		}
		else {
			delete stage;
		}
	}
	
}

void TileMaker::TileBlockMenu(vector<vector<CTileBlock>>& vvec)
{
	ImGui::BeginChild("LeftTops", ImVec2(305, 450), true, 0);


	if (ImGui::Button("Create New TileBlock")) {
		m_curTileBlock = m_newTileBlock;
		m_curBlockName = NewBlockName;
	}
	if (ImGui::Button("TileBlock Save")) {
		if (m_iTypeCursor == -1) {
			MessageBox(nullptr, L"타일블록 타입을 지정해주세요", L"타일메이커", MB_OK);
		}
		else {
			MessageBox(nullptr, L"타일블록을 저장했습니다.", L"타일메이커", MB_OK);
			vvec[(int)m_iTypeCursor].push_back(m_curTileBlock);
			m_curTileBlock = m_newTileBlock;
		}
	}

	// 타일블럭 정보 입력 칸 필요
	ButtonTitle("Select Type");
	const char* types[(int)TileBlockType::END] = { "None", "Entrance", "Entrance_Fall", "Exit", "Exit_Drop", "Normal", "Fall", "Drop", "Fall_Drop", "Side", "NeverCrash"};
	ImGui::Combo("##selecttileblocktype", &m_iTypeCursor, types, IM_ARRAYSIZE(types));


	// 블럭타일 이미지 띄우기
	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
	int width = 280;
	int height = (float)m_texBlockTile.Get()->GetHeight() / m_texBlockTile.Get()->GetWidth() * width;
	ImVec2 ImgSize = { (float)width, (float)height };

	ImVec2 imagePos = ImGui::GetCursorScreenPos();
	ImGui::Image(m_texBlockTile->GetSRV().Get(), ImgSize, uv_min, uv_max, tint_col, border_col);

	ImVec2 GridSize = ImgSize;
	GridSize.x /= BLOCKTILEX;
	GridSize.y /= BLOCKTILEY;

	static vector<float> mousepos = { 0, 0 };

	static vector<int> gridIdx = { 0, 0 };

	static int idx = 0;
	if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
	{
		imagePos = ImGui::GetCursorScreenPos();
		ImVec2 mousePos = ImGui::GetMousePos();
		ImVec2 uv = (mousePos - imagePos) / ImgSize;
		mousepos = { uv.x, 1 + uv.y };
		gridIdx[0] = ((int)(mousepos[0] * BLOCKTILEX) % (int)GridSize.x) * GridSize.x;
		gridIdx[1] = ((int)(mousepos[1] * BLOCKTILEY) % (int)GridSize.y) * GridSize.y;

		idx = math::RowColToIdx(Vec2((float)gridIdx[0] / 70, (float)gridIdx[1] / 70), Vec2(BLOCKTILEX, BLOCKTILEY));
		m_curType = (BlockTileType)idx;
	}

	// 현재 선택된 블럭타일 띄우기
	ButtonTitle("Current Tile");
	ImGui::SameLine();
	uv_min = { gridIdx[0] / ImgSize.x, gridIdx[1] / ImgSize.y };
	uv_max = uv_min + ImVec2((float)67 / width, (float)67 / width);
	ImVec2 TileSize = { 70, 70 };

	ImGui::Image(m_texBlockTile->GetSRV().Get(), TileSize, uv_min, uv_max, tint_col, border_col);


	ImGui::EndChild();
}

void TileMaker::SelectBackground()
{
	ButtonTitle("Background");
	VecCombo("##backgrounds", m_vecBackgroundPaths, m_iBGIdx);

	ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
	int width = 250;
	int height = (float)m_vecBackgrounds[m_iBGIdx].Get()->GetHeight() / m_vecBackgrounds[m_iBGIdx].Get()->GetWidth() * width;
	ImVec2 ImgSize = { (float)width, (float)height };

	ImGui::Image(m_vecBackgrounds[m_iBGIdx]->GetSRV().Get(), ImgSize, uv_min, uv_max, tint_col, border_col);
}

void TileMaker::PrintTileBlock(CTileBlock& _tileblock)
{
	for (int row = 0; row < TILEBLOCKSIZEY; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			BlockTileType curType = _tileblock.GetTileType(row, col);
			Vec2 idx = math::IdxToRowCol((int)curType, Vec2(BLOCKTILEX, BLOCKTILEY));

			ImVec2 ImgSize = ImVec2(70, 70); // 이미지 크기
			ImVec2 uv0 = ImVec2((float)idx.y * 70.f / 280.f, (float)idx.x * 70.f / 280.f); // 텍스처의 좌측 상단 UV 좌표
			ImVec2 uv1 = ImVec2(uv0.x + 67.f / 280.f, uv0.y + 67.f / 280.f); // 텍스처의 우측 하단 UV 좌표
			ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // 버튼 배경색 (투명)
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

			// 투명 버튼 설정
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0)); // 버튼 배경을 투명하게
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.1f)); // 호버 시 약간의 색상 변경
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.2f)); // 클릭 시 약간 더 진한 색상 변경

			// 이미지 위에 투명 버튼 오버레이
			static int i = 0;
			string key = std::to_string(row * TILEBLOCKSIZEX + col);
			if (ImGui::ImageButton(key.c_str(), m_texBlockTile->GetSRV().Get(), ImgSize, uv0, uv1, bg_col, tint_col)) {
				_tileblock.SetTileType(m_curType, row, col);
			}

			// 스타일 색상 복원
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
}

void TileMaker::PrintStageBlocks(vector<vector<CTileBlock>>& vvec)
{
	ButtonTitle("Current");
	ImGui::Button(m_curBlockName.c_str());
	ImGui::Separator();
	ImGui::NewLine();

	for (int type = 0; type < vvec.size(); type++) {
		auto tileblocks = vvec[type];
		if (tileblocks.size() == 0) continue;

		string strType = TileBlockTypeStrings[type];
		ButtonTitle(strType.c_str());
		ImGui::NewLine();
		for (int idx = 0; idx < tileblocks.size(); idx++) {

			string key = strType + std::to_string(idx);
			ImGui::Dummy(ImVec2(5.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button(key.c_str())) {
				LoadStageBlock(vvec, type, idx);
				m_iTypeCursor = type;
				m_curBlockName = key;
			}

			string deletekey = "X##";
			deletekey += key;
			ImGui::SameLine();
			if (ImGui::Button(deletekey.c_str())) {
				DeleteStageBlock(vvec, type, idx);
				m_curBlockName = NewBlockName;
			}
		}
	}
}

void TileMaker::LoadStageBlock(vector<vector<CTileBlock>> vvec, int type, int idx)
{
	m_curTileBlock = vvec[type][idx];
}

void TileMaker::DeleteStageBlock(vector<vector<CTileBlock>>& vvec, int type, int idx)
{
	auto del = vvec[type].begin() + idx;

	vvec[type].erase(vvec[type].begin() + idx);

	m_curTileBlock = m_newTileBlock;
	MessageBox(nullptr, L"타일블록 타입을 제거했습니다", L"타일메이커", MB_OK);
}

void TileMaker::SortTileBlocks(CStagePack* _stage)
{
	auto map = _stage->GetList();
	m_vecTileBlocks.clear();
	m_vecTileBlocks.resize((int)TileBlockType::END);
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		auto vec = iter->second;
		for (auto tileblock : vec) {
			m_vecTileBlocks[(int)iter->first].push_back(tileblock);
		}
	}
}

void TileMaker::SaveStage(CStagePack* _stage, vector<vector<CTileBlock>> _vvec)
{
	string filename = ToString(CPathMgr::GetContentPath()) + "stage\\";
	filename += m_StageName;
	filename += ".sp";
	ofstream fout(filename, std::ios::out | std::ios::trunc);

	FillTileBlocks(_stage, _vvec);
	_stage->SetBackground(m_vecBackgrounds[m_iBGIdx]);

	if (fout.is_open()) {
		fout << *_stage;
	}
}

void TileMaker::SaveStage(CStagePack* _stage, vector<vector<CTileBlock>> _vvec, int _num)
{
	string filename = ToString(CPathMgr::GetContentPath());
	filename += m_StageNames[_num];

	ofstream fout(filename, std::ios::out | std::ios::trunc);

	FillTileBlocks(_stage, _vvec);
	_stage->SetBackground(m_vecBackgrounds[m_iBGIdx]);

	if (fout.is_open()) {
		fout << *_stage;
	}
}

void TileMaker::FillTileBlocks(CStagePack* _stage, vector<vector<CTileBlock>> _vvec)
{
	for (int type = 0; type < _vvec.size(); type++) {
		_stage->ClearTileBlock((TileBlockType)type);
		for (int i = 0; i < _vvec[type].size(); i++) {
			_stage->AddTileBlock((TileBlockType)type, _vvec[type][i]);
		}
	}
}

void TileMaker::ClearTileBlocks(vector<vector<CTileBlock>>& _blocks)
{
	_blocks.clear();
	_blocks.resize((int)TileBlockType::END);
}




#include "pch.h"
#include "TileMaker.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CPathMgr.h>

#include <Scripts/CStage.h>
#include <Scripts/CTileBlock.h>

TileMaker::TileMaker()
	: UI("TileMaker", UITileMakerName)
	, m_curStage(nullptr)
	, m_state(TileMakerState::NONE)
{
	wstring blocktilepath = L"texture\\tilemap\\blocktile.png";
	m_texBlockTile = ASSET_LOAD(CTexture, blocktilepath);

	ClearStage();
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
			m_state = TileMakerState::New;
			m_curStage = m_newStage;
			m_vecNewTileBlocks.clear();
			m_vecNewTileBlocks.resize((int)TileBlockType::END);
		}
		if (ImGui::Button("Stage Modify")) {
			m_state = TileMakerState::Modify;
			m_StageNames.clear();
			LoadAllPath("stage", m_StageNames);
			LoadAllStages();
			SortTileBlocks(m_vecStages[0]);
		}
	}



	// �������� ����
	if (m_state == TileMakerState::New) {
		ImGui::BeginChild("LeftTops", ImVec2(320, 800), true, 0);
		ReturnButton();

		ImGui::SameLine();

		if(ImGui::Button("Stage Save")){
			if (m_StageName[0] == 0) {
				MessageBox(nullptr, L"�������� �̸��� �������ּ���", L"Ÿ�ϸ���Ŀ", MB_OK);
			}
			else {
				MessageBox(nullptr, L"���������� ����Ǿ����ϴ�", L"Ÿ�ϸ���Ŀ", MB_OK);

				SaveStage(m_newStage, m_vecNewTileBlocks);

				ClearStage();

				m_state = TileMakerState::NONE;
			}
		}

		ButtonTitle("Stage Name");
		ImGui::InputText("##stagename", m_StageName, 32);
		TileBlockMenu(m_vecNewTileBlocks);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockMaps", ImVec2(200, 800), true, 0);
		PrintStageBlocks(m_vecNewTileBlocks);
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockTiles", ImVec2(1000,800), true, 0);
		PrintTileBlock(m_curTileBlock);
		ImGui::EndChild();
		
	}

	// ���� �������� ����
	if (m_state == TileMakerState::Modify) {
		ImGui::BeginChild("LeftTops", ImVec2(320, 800), true, 0);
		ReturnButton();
		ImGui::SameLine();
		if (ImGui::Button("Stage Save")) {
			MessageBox(nullptr, L"���������� ����Ǿ����ϴ�", L"Ÿ�ϸ���Ŀ", MB_OK);

			SaveStage(m_curStage, m_vecTileBlocks);

			ClearStage();

			m_state = TileMakerState::NONE;
		}

		ButtonTitle("Select Stage");

		static int comboidx = 0;
		int prev = comboidx;
		VecCombo("##tilemaker1", m_StageNames, comboidx);
		if (prev != comboidx) {
			SortTileBlocks(m_vecStages[comboidx]);
		}

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

void TileMaker::ReturnButton()
{
	if (ImGui::Button("Return")) {
		m_state = TileMakerState::NONE;
	}
}

void TileMaker::LoadAllStages()
{
	Delete_Vec(m_vecStages);
	m_vecStages.clear();

	for (int i = 0; i < m_StageNames.size(); i++) {
		string path = ToString(CPathMgr::GetContentPath());
		path += m_StageNames[i];

		CStage* stage = new CStage;
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


	static int item_current_1 = -1; // If the selection isn't within 0..count, Combo won't display a preview
	if (ImGui::Button("Create New TileBlock")) {
		m_curTileBlock = m_newTileBlock;
	}
	if (ImGui::Button("TileBlock Save")) {
		if (item_current_1 == -1) {
			MessageBox(nullptr, L"Ÿ�Ϻ��� Ÿ���� �������ּ���", L"Ÿ�ϸ���Ŀ", MB_OK);
		}
		else {
			MessageBox(nullptr, L"Ÿ�Ϻ����� �����߽��ϴ�.", L"Ÿ�ϸ���Ŀ", MB_OK);
			vvec[(int)item_current_1].push_back(m_curTileBlock);
			m_curTileBlock = m_newTileBlock;
		}
	}

	// Ÿ�Ϻ��� ���� �Է� ĭ �ʿ�
	ButtonTitle("Select Type");
	const char* types[(int)TileBlockType::END] = { "None", "Entrance", "Entrance_Fall", "Exit", "Exit_Drop", "Normal", "Fall", "Drop", "Fall_Drop", "Side" };
	ImGui::Combo("##selecttileblocktype", &item_current_1, types, IM_ARRAYSIZE(types));


	// ����Ÿ�� �̹��� ����
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

	// ���� ���õ� ����Ÿ�� ����
	ButtonTitle("Current Tile");
	ImGui::SameLine();
	uv_min = { gridIdx[0] / ImgSize.x, gridIdx[1] / ImgSize.y };
	uv_max = uv_min + ImVec2((float)67 / width, (float)67 / width);
	ImVec2 TileSize = { 70, 70 };

	ImGui::Image(m_texBlockTile->GetSRV().Get(), TileSize, uv_min, uv_max, tint_col, border_col);


	ImGui::EndChild();
}

void TileMaker::PrintTileBlock(CTileBlock& _tileblock)
{
	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			BlockTileType curType = _tileblock.GetTileType(row, col);
			Vec2 idx = math::IdxToRowCol((int)curType, Vec2(BLOCKTILEX, BLOCKTILEY));

			ImVec2 ImgSize = ImVec2(70, 70); // �̹��� ũ��
			ImVec2 uv0 = ImVec2((float)idx.y * 70.f / 280.f, (float)idx.x * 70.f / 280.f); // �ؽ�ó�� ���� ��� UV ��ǥ
			ImVec2 uv1 = ImVec2(uv0.x + 67.f / 280.f, uv0.y + 67.f / 280.f); // �ؽ�ó�� ���� �ϴ� UV ��ǥ
			ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // ��ư ���� (����)
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

			// ���� ��ư ����
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0)); // ��ư ����� �����ϰ�
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.1f)); // ȣ�� �� �ణ�� ���� ����
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.2f)); // Ŭ�� �� �ణ �� ���� ���� ����

			// �̹��� ���� ���� ��ư ��������
			static int i = 0;
			string key = std::to_string(row * TILEBLOCKSIZE + col);
			if (ImGui::ImageButton(key.c_str(), m_texBlockTile->GetSRV().Get(), ImgSize, uv0, uv1, bg_col, tint_col)) {
				_tileblock.SetTileType(m_curType, row, col);
			}

			// ��Ÿ�� ���� ����
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
}

void TileMaker::PrintStageBlocks(vector<vector<CTileBlock>>& vvec)
{

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
			}

			string deletekey = "X##";
			deletekey += key;
			ImGui::SameLine();
			if (ImGui::Button(deletekey.c_str())) {
				DeleteStageBlock(vvec, type, idx);
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
	MessageBox(nullptr, L"Ÿ�Ϻ��� Ÿ���� �����߽��ϴ�", L"Ÿ�ϸ���Ŀ", MB_OK);
}

void TileMaker::SortTileBlocks(CStage* _stage)
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

void TileMaker::SaveStage(CStage* _stage, vector<vector<CTileBlock>> _vvec)
{
	ofstream fout;
	string filename = ToString(CPathMgr::GetContentPath()) + "stage\\";
	filename += m_StageName;
	filename += ".st";
	fout.open(filename);

	FillTileBlocks(_stage, _vvec);

	if (fout.is_open()) {
		fout << *_stage;
	}
}

void TileMaker::SaveStage(CStage* _stage, vector<vector<CTileBlock>> _vvec, int _num)
{
	ofstream fout;
	string filename = ToString(CPathMgr::GetContentPath()) + "stage\\";
	filename += m_StageNames[_num];
	filename += ".st";
	fout.open(filename);

	FillTileBlocks(_stage, _vvec);

	if (fout.is_open()) {
		fout << *_stage;
	}
}

void TileMaker::FillTileBlocks(CStage* _stage, vector<vector<CTileBlock>> _vvec)
{
	for (int type = 0; type < _vvec.size(); type++) {
		for (int i = 0; i < _vvec[type].size(); i++) {
			_stage->AddTileBlock((TileBlockType)type, _vvec[type][i]);
		}
	}
}

void TileMaker::ClearStage()
{
	if (m_newStage) delete m_newStage;
	m_curStage = m_newStage = new CStage;
	
	m_vecTileBlocks.clear();
	m_vecTileBlocks.resize((int)TileBlockType::END);

}


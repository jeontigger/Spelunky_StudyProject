#include "pch.h"
#include "TileMaker.h"

#include <Engine/CAssetMgr.h>

#include <Scripts/CStage.h>
#include <Scripts/CTileBlock.h>

TileMaker::TileMaker()
	: UI("TileMaker", UITileMakerName)
	, m_curStage(nullptr)
	, m_curTileBlock(nullptr)
	, m_state(TileMakerState::New)
{
	LoadAllPath("stage", m_StageNames);
	LoadAllStages();
	m_newStage = new CStage;
	m_newTileBlock = new CTileBlock;

	wstring blocktilepath = L"texture\\tilemap\\blocktile.png";
	m_texBlockTile = ASSET_LOAD(CTexture, blocktilepath);

}

TileMaker::~TileMaker()
{
	if (m_newStage)
		delete m_newStage;
	if (m_newTileBlock)
		delete m_newTileBlock;
}

void TileMaker::render_update()
{
	if (m_state == TileMakerState::NONE) {
		if (ImGui::Button("Make New Stage")) {
			m_state = TileMakerState::New;
		}
		if (ImGui::Button("Stage Modify")) {
			m_state = TileMakerState::Modify;
		}
	}



	// �������� ����
	if (m_state == TileMakerState::New) {
		ImGui::BeginChild("LeftTops", ImVec2(320, 800), true, 0);
		ReturnButton();

		ImGui::SameLine();

		if(ImGui::Button("Stage Save")){

		}

		ButtonTitle("Stage Name");
		ImGui::InputText("##stagename", m_StageName, 32);
		TileBlockMenu();
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockMaps", ImVec2(200, 800), true, 0);
		PrintStageBlocks();
		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginChild("BlockTiles", ImVec2(1000,800), true, 0);
		PrintTileBlock();
		ImGui::EndChild();
		
	}

	// ���� �������� ����
	if (m_state == TileMakerState::Modify) {
		ReturnButton();
		ButtonTitle("Select Stage");

		static int comboidx = 0;
		VecCombo("##tilemaker1", m_StageNames, comboidx);
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

}

void TileMaker::TileBlockMenu()
{
	ImGui::BeginChild("LeftTops", ImVec2(305, 450), true, 0);


	static int item_current_1 = -1; // If the selection isn't within 0..count, Combo won't display a preview
	if (ImGui::Button("TileBlock Save")) {
		if (item_current_1 == -1) {
			MessageBox(nullptr, L"Ÿ�Ϻ�� Ÿ���� �������ּ���", L"Ÿ�ϸ���Ŀ", MB_OK);
		}
		else {
			m_newStage->AddTileBlock((TileBlockType)item_current_1, m_newTileBlock);
			MessageBox(nullptr, L"Ÿ�Ϻ���� �����߽��ϴ�.", L"Ÿ�ϸ���Ŀ", MB_OK);
			m_newTileBlock = new CTileBlock;
			SortTileBlocks(m_newStage);
		}
	}

	// Ÿ�Ϻ� ���� �Է� ĭ �ʿ�
	ButtonTitle("Select Type");
	const char* types[(int)TileBlockType::END] = { "None", "Entrance", "Entrance_Fall", "Exit", "Exit_Drop", "Normal", "Fall", "Drop", "Fall_Drop", "Side" };
	ImGui::Combo("##selecttileblocktype", &item_current_1, types, IM_ARRAYSIZE(types));


	// ��Ÿ�� �̹��� ����
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

	// ���� ���õ� ��Ÿ�� ����
	ButtonTitle("Current Tile");
	ImGui::SameLine();
	uv_min = { gridIdx[0] / ImgSize.x, gridIdx[1] / ImgSize.y };
	uv_max = uv_min + ImVec2((float)67 / width, (float)67 / width);
	ImVec2 TileSize = { 70, 70 };

	ImGui::Image(m_texBlockTile->GetSRV().Get(), TileSize, uv_min, uv_max, tint_col, border_col);


	ImGui::EndChild();
}

void TileMaker::PrintTileBlock()
{
	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			BlockTileType curType = m_newTileBlock->GetTileType(row, col);
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
				m_newTileBlock->SetTileType(m_curType, row, col);
			}

			// ��Ÿ�� ���� ����
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}
}

void TileMaker::PrintStageBlocks()
{

	for (int i = 0; i < m_vecTileBlocks.size(); i++) {
		auto tileblocks = m_vecTileBlocks[i];
		if (tileblocks.size() == 0) continue;
		string strType = TileBlockTypeStrings[i];
		ButtonTitle(strType.c_str());
		ImGui::NewLine();
		for (int j = 0; j < tileblocks.size(); j++) {
			string key = strType + std::to_string(j);
			ImGui::Dummy(ImVec2(5.0f, 0.0f));
			ImGui::SameLine();
			if (ImGui::Button(key.c_str())) {

			}
		}
	}
}

void TileMaker::SortTileBlocks(CStage* _stage)
{
	auto map = _stage->GetList();
	m_vecTileBlocks.clear();
	m_vecTileBlocks.resize((int)TileBlockType::END);
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		m_vecTileBlocks[(int)iter->first].push_back(iter->second);
	}
}


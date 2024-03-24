#include "pch.h"
#include "UI.h"


UI::UI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_Parent(nullptr)
	, m_bModal(false)
{
}

UI::~UI()
{
	Delete_Vec(m_vecChildUI);
}

void UI::tick()
{

}

void UI::render()
{
	if (!m_bActive)
		return;

	bool Active = m_bActive;

	if (nullptr == GetParentUI())
	{
		// Modal
		if (!m_bModal)
		{
			ImGui::Begin(string(m_strName + m_strID).c_str(), &Active);

			// 활성화, 비활성화 전환이 발생한 경우에는 Activate or Deactivate 를 호출시킨다.
			if (Active != m_bActive)
			{
				m_bActive = Active;

				if (m_bActive)
					Activate();
				else
					Deactivate();
			}

			render_update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				m_vecChildUI[i]->render();
			}

			ImGui::End();
		}

		// Modal
		else
		{
			ImGui::OpenPopup(string(m_strName + m_strID).c_str());
			if (ImGui::BeginPopupModal(string(m_strName + m_strID).c_str(), &Active))
			{
				render_update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					m_vecChildUI[i]->render();
				}

				ImGui::EndPopup();
			}

			else
			{
				// 활성화, 비활성화 전환이 발생한 경우에는 Activate or Deactivate 를 호출시킨다.
				if (Active != m_bActive)
				{
					m_bActive = Active;

					if (m_bActive)
						Activate();
					else
						Deactivate();
				}
			}
		}		
	}

	// Child UI 인 경우
	else
	{
		ImGui::BeginChild(string(m_strName + m_strID).c_str(), m_vSize);

		render_update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->render();
		}

		ImGui::EndChild();
	}
}

void UI::ButtonTitle(const char* Content)
{
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::Button(Content);

	ImGui::PopStyleColor(3);
	ImGui::PopID();
	ImGui::SameLine();
}


void UI::VecCombo(const char* ID, const vector<string>& vec, int& item_current_idx)
{
	const char* combo_preview_value = vec[item_current_idx].c_str();

	if (ImGui::BeginCombo(ID, combo_preview_value, 0))
	{
		for (int n = 0; n < vec.size(); n++)
		{
			const bool is_selected = (item_current_idx == n);
			if (ImGui::Selectable(vec[n].c_str(), is_selected))
				item_current_idx = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

// 간단한 검색 가능한 콤보 박스 구현
bool UI::SearchableComboBox(const char* id, int* current_item, std::vector<std::string>& items) {
	// 검색 문자열을 저장할 버퍼
	static char searchBuffer[256] = "";

	// 콤보 박스와 검색 필드의 고유 ID를 생성하기 위해 사용자가 제공한 id를 사용
	std::string combo_box_id = std::string("##ComboBox") + id;
	std::string search_field_id = std::string("##SearchField") + id;

	// 검색 필드
	ImGui::InputText(search_field_id.c_str(), searchBuffer, IM_ARRAYSIZE(searchBuffer));

	if (ImGui::BeginCombo(combo_box_id.c_str(), items[*current_item].c_str())) {
		for (int i = 0; i < items.size(); i++) {
			// 검색어가 비어 있지 않고 항목이 검색어를 포함하지 않는 경우 건너뛴다

			string lowerItem = items[i];
			std::transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), [](unsigned char c) { return std::tolower(c); });

			string lowersearch = searchBuffer;
			std::transform(lowersearch.begin(), lowersearch.end(), lowersearch.begin(), [](unsigned char c) { return std::tolower(c); });

			if (searchBuffer[0] != '\0' && lowerItem.find(lowersearch) == std::string::npos) {
				continue;
			}

			// 항목 선택 가능하게 만들기
			bool is_selected = (*current_item == i);
			if (ImGui::Selectable(items[i].c_str(), is_selected)) {
				*current_item = i;
			}

			// 항목이 선택된 경우, 콤보 박스를 닫고 해당 항목으로 스크롤하기
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	return true;
}

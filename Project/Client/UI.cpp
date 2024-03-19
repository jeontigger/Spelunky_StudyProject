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

#include <filesystem>
void UI::LoadAllPath(string _strDirectoryPath, vector<string>&vec)
{
	string path = ToString(CPathMgr::GetContentPath());
	path += _strDirectoryPath;

	namespace fs = std::filesystem;

	for (const auto& entry : fs::directory_iterator(path)) {
		string str = entry.path().string();
		str = str.substr(str.find(_strDirectoryPath));
		vec.push_back(str);
	}
}
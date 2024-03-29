#include "pch.h"
#include "FSMUI.h"

#include <Scripts/CStateMgr.h>

FSMUI::FSMUI()
	: AssetUI("FSM", "##FSM", ASSET_TYPE::FSM)
{
	// 스테이트 목록 가져오기
    vector<wstring> vec;
    CStateMgr::GetStateInfo(vec);
    for (int i = 0; i < vec.size(); i++) {
        m_vecNames.push_back(ToString(vec[i]));
    }
}

FSMUI::~FSMUI()
{
}

void FSMUI::render_update()
{
	AssetUI::render_update();

    Save();
	// 스테이트 목록 보여주기 + change state
    ImGui::Separator();
    StateList();

	// 스테이트 추가할 수 있게 하기
    ImGui::Separator();
    AddState();
}

void FSMUI::Activate()
{
    AssetUI::Activate();
    m_target = (CFSM*)GetAsset().Get();
    //strcpy(m_NameBuff, ToString(m_target->GetKey()).c_str());
}

#include "Content.h"
void FSMUI::Save()
{
    ImGui::Text("New Name"); ImGui::SameLine();
    ImGui::InputText("##FSMNameBox", m_NameBuff, sizeof(m_NameBuff)); ImGui::SameLine();
    if(ImGui::Button("Save")) {
        string name = string(m_NameBuff);
        name = "fsm\\" + name + ".fsm";
        m_target->SetName(name);
        m_target->Save(ToWString(name));
        auto content = (Content*)UIMGR->FindUI(UIContentName);
        content->ResetContent();
    }
}

void FSMUI::StateList()
{
    map<wstring, CState*>& states = m_target->GetStates();
    for (auto iter = states.begin(); iter != states.end();) {
        string statename = ToString(iter->first);
        ImGui::InputText("##StateName", (char*)statename.c_str(), statename.length(), ImGuiInputTextFlags_ReadOnly);
        ImGui::SameLine();

        ImGui::PushID(0);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

        if (ImGui::Button("Delete")) {
            delete iter->second;
            iter = states.erase(iter);
            MessageBox(nullptr, L"State가 삭제되었습니다.", L"State", 0);
        }
        else {
            ++iter;
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
}

void FSMUI::AddState()
{

    ButtonTitle("AddState");
    
    static int current_item = 0;
    if (ImGui::Button("Add##addstate")) {
        CState* state = CStateMgr::GetState(current_item);
        wstring name = CStateMgr::GetStateName(state);
        m_target->AddState(name, state);
    }
    SearchableComboBox("addstateuicombo", &current_item, m_vecNames);

}

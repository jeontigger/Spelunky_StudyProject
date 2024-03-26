#include "pch.h"
#include "AddComponentUI.h"

#include <Engine/CGameObject.h>

#include <Scripts/CScriptMgr.h>

#include "CImGuiMgr.h"
#include "Inspector.h"

AddComponentUI::AddComponentUI()
	: UI("AddComponent", UIAddComponentName)
{
    for (int i = 0; i < (int)COMPONENT_TYPE::END; i++) {
        m_vecComponentStrings.push_back(COMPONENT_TYPE_STRING[i]);
    }
    vector<wstring> vec;
    CScriptMgr::GetScriptInfo(vec);
    for (int i = 0; i < vec.size(); i++) {
        m_vecComponentStrings.push_back(ToString(vec[i]));
    }
    SetSize(ImVec2(0.f, 120.f));
}

AddComponentUI::~AddComponentUI()
{
}


void AddComponentUI::render_update()
{
    ImGui::Separator();

	ButtonTitle("AddComponent");

    static int current_item = 0;
    if (ImGui::Button("Add##addcomponent")) {
        if (current_item < (int)COMPONENT_TYPE::END) {
            m_target->AddComponent((COMPONENT_TYPE)current_item);
        }
        else {
            CScript* script = CScriptMgr::GetScript(current_item - (int)COMPONENT_TYPE::END);
            m_target->AddComponent((CComponent*)script);
        }
        
        Inspector* inspector = (Inspector*)UIMGR->FindUI(UIInspectorName);
        inspector->SetTargetObject(m_target);
    }

    SearchableComboBox("addcomponentuicombo", &current_item, m_vecComponentStrings);
}

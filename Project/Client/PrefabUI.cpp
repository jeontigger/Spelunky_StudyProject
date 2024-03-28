#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CPrefab.h>

#include "Inspector.h"

PrefabUI::PrefabUI()
	: AssetUI("Prefab", "##Prefab", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::render_update()
{
	AssetUI::render_update();


    static UINT layercheck = 0;
    int maxcol = 4;
    static int layeridx = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < maxcol; j++) {
            auto layer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(i * maxcol + j);
            if (layer == nullptr) continue;
            //if (layer->GetName() == L"") continue;
            string name = ToString(layer->GetName());
            if (name != L"") {
                name += "##nonamelayer";
            }
            name += std::to_string(i * maxcol + j);
            bool lc = (layercheck >> (i * maxcol + j)) & 1;
            if (ImGui::Checkbox(name.c_str(), &lc)) {
                layercheck = 0;
                layercheck |= (1 << (i * maxcol + j));
                layeridx = i * maxcol + j;
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

	if(ImGui::Button("Spawn")) {
		auto obj = m_Prefab->Instantiate();
		GamePlayStatic::SpawnGameObject(obj, layeridx);
	}

    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.8f, 0.8f));
    if (ImGui::Button("Delete Prefab")) {
        wstring path = CPathMgr::GetContentPath();
        path += L"prefab\\" + m_Prefab->GetProtoType()->GetName();
        path += L".pref";
        if (std::remove(ToString(path).c_str()) != 0) {
            MessageBox(nullptr, L"삭제되지 않는 객체입니다", L"프리팹 삭제", 0);
        }
        else {
            MessageBox(nullptr, L"삭제되었습니다", L"프리팹 삭제", 0);
        }
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void PrefabUI::Activate()
{
	AssetUI::Activate();

	m_Prefab = (CPrefab*)GetAsset().Get();
	
}

#include "pch.h"
#include "Inspector.h"

#include <Engine/CTransform.h>
#include <Engine\CPrefab.h>

#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "ScriptUI.h"
#include "AddComponentUI.h"

#include "AssetUI.h"


Inspector::Inspector()
	: UI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	// 자식 UI 생성
	CreateChildUI();
}

Inspector::~Inspector()
{

}

void Inspector::tick()
{
}

void Inspector::render_update()
{
	if (nullptr == m_TargetObject)
		return;

	if (nullptr != m_TargetObject)
	{

		static char* nameBuf[32];
		ImGui::InputText("##modifyname", (char*)nameBuf, 32);

		string strName((char*)nameBuf);
		m_TargetObject->SetName(strName);

		if (ImGui::Button("Make New Prefab")) {
			Ptr<CPrefab> prefab = new CPrefab;
			CGameObject* obj = m_TargetObject->Clone();
			prefab->SetGameObject(obj);
			wstring path = L"prefab\\";
			path += ToWString(strName);
			path += L".pref";
			CAssetMgr::GetInst()->AddAsset(path, prefab.Get());
			prefab->Save(path);

			MessageBox(nullptr, L"프리팹을 생성했습니다", L"프리팹 생성", 0);
		}

		ImGui::SameLine();

		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.8f, 0.8f));
		if (ImGui::Button("Delete Object")) {
			GamePlayStatic::DestroyGameObject(m_TargetObject);
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}
}

void Inspector::SetTargetObject(CGameObject* _Object)
{
	// Target 오브젝트 설정
	m_TargetObject = _Object;

	m_uiAddComponent->Activate();
	m_uiAddComponent->SetTargetObject(_Object);

	// 해당 오브젝트가 보유하고 있는 컴포넌트에 대응하는 컴포넌트UI 활성화
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrComUI[i])
		{
			m_arrComUI[i]->SetTargetObject(_Object);
		}
	}

	// 해당 오브젝트가 보유하고 있는 Script 에 맞추어서 ScriptUI 를 활성화 시킨다.
	if (nullptr == _Object)
	{
		for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
		{
			m_vecScriptUI[i]->Deactivate();
		}
	}
	else
	{
		if (m_vecScriptUI.size() < _Object->GetScripts().size())
		{
			ResizeScriptUI(_Object->GetScripts().size());
		}

		const vector<CScript*>& vecScripts = _Object->GetScripts();
		for (size_t i = 0; i < vecScripts.size(); ++i)
		{
			m_vecScriptUI[i]->SetScript(vecScripts[i]);			
		}
	}


	// AssetUI 비활성화
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> _Asset)
{
	SetTargetObject(nullptr);

	m_uiAddComponent->Deactivate();

	m_TargetAsset = _Asset;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
		
	if(nullptr != m_TargetAsset)
	{
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->SetAsset(_Asset);
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->Activate();
	}	
}

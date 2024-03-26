#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMeshRender.h>

#include "CImGuiMgr.h"
#include "ListUI.h"
#include "Inspector.h"


MeshRenderUI::MeshRenderUI()
	: ComponentUI("MeshRender", "##MeshRender", COMPONENT_TYPE::MESHRENDER)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComopnentTitle("MeshRender");
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::render_update()
{
	ComponentUI::render_update();

	CGameObject* pTarget = GetTargetObject();
	CMeshRender* pMeshRender = pTarget->MeshRender();

	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMtrl = pMeshRender->GetMaterial();

	string meshname, mtrlname;

	if (nullptr != pMesh)
	{
		meshname = ToString(pMesh->GetKey()).c_str();
	}
	if (nullptr != pMtrl)
	{
		mtrlname = ToString(pMtrl->GetKey()).c_str();
	}
		
	ImGui::Text("Mesh    ");
	ImGui::SameLine(); 
	ImGui::InputText("##MeshName", (char*)meshname.c_str(), meshname.length(), ImGuiInputTextFlags_ReadOnly);

	// Mesh Drop 체크
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::MESH == pAsset->GetType())
			{
				GetTargetObject()->MeshRender()->SetMesh((CMesh*)pAsset);
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##MeshBtn", ImVec2(20, 20)))
	{
		// 리스트 UI
		ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

		vector<string> vecMeshName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::MESH, vecMeshName);

		pListUI->AddString(vecMeshName);
		//pListUI->SetDbClickCallBack(MeshSelect);
		pListUI->SetDbClickDelegate(this, (Delegate_1)&MeshRenderUI::MeshSelect);
		pListUI->Activate();
	}

	ImGui::Text("Material"); 
	ImGui::SameLine(); 
	ImGui::InputText("##MtrlName", (char*)mtrlname.c_str(), mtrlname.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();

	// Material Drop 체크
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::MATERIAL == pAsset->GetType())
			{
				GetTargetObject()->MeshRender()->SetMaterial((CMaterial*)pAsset);
			}
		}
		ImGui::EndDragDropTarget();
	}


	if (ImGui::Button("##MtrlBtn", ImVec2(20, 20)))
	{
		// 리스트 UI
		ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

		vector<string> vecMtrlName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::MATERIAL, vecMtrlName);

		pListUI->AddString(vecMtrlName);
		pListUI->SetDbClickDelegate(this, (Delegate_1)&MeshRenderUI::MaterialSelect);
		pListUI->Activate();
	}

	int scalarCnt = 0;
	if (!pMtrl.Get())
		return;

	for (int i = 0; i < (int)SCALAR_PARAM::END; i++) {
		SCALAR_PARAM param = (SCALAR_PARAM)i;
		string desc = pMtrl->IsUsingScalarParam(param);
		if (desc[0] == 0|| desc == EMPTYSYMBOL) continue;

		ImGui::Text(desc.c_str());
		ImGui::SameLine();
		scalarCnt++;
		string scalarKey = "##meshrenderScalarKey" + to_string(i);
		string scalarContent = "";

			switch ((SCALAR_PARAM)i)
			{
			case SCALAR_PARAM::INT_0:
			case SCALAR_PARAM::INT_1:
			case SCALAR_PARAM::INT_2:
			case SCALAR_PARAM::INT_3:
				scalarContent = to_string(*(int*)pMtrl->GetScalarParam(param));
			break;
			case SCALAR_PARAM::FLOAT_0:
			case SCALAR_PARAM::FLOAT_1:
			case SCALAR_PARAM::FLOAT_2:
			case SCALAR_PARAM::FLOAT_3:
				scalarContent = to_string(*(float*)pMtrl->GetScalarParam(param));
			break;
			case SCALAR_PARAM::VEC2_0:
			case SCALAR_PARAM::VEC2_1:
			case SCALAR_PARAM::VEC2_2:
			case SCALAR_PARAM::VEC2_3:
			{
				Vec2 vec = *(Vec2*)pMtrl->GetScalarParam(param);
				scalarContent = to_string(vec.x) + " | " + to_string(vec.y);
			}
			break;
			case SCALAR_PARAM::VEC4_0:
			case SCALAR_PARAM::VEC4_1:
			case SCALAR_PARAM::VEC4_2:
			case SCALAR_PARAM::VEC4_3:
			{
				Vec4 vec4 = *(Vec4*)pMtrl->GetScalarParam(param);
				scalarContent = to_string(vec4.x) + " | " + to_string(vec4.y) + " | " + to_string(vec4.z) + " | " + to_string(vec4.w);
			}
			break;
			case SCALAR_PARAM::MAT_0:
			case SCALAR_PARAM::MAT_1:
			case SCALAR_PARAM::MAT_2:
			case SCALAR_PARAM::MAT_3:
				break;
			}
		ImGui::InputText(scalarKey.c_str(), (char*)scalarContent.c_str(), scalarContent.length(), ImGuiInputTextFlags_ReadOnly);
	}


	int texCnt = 0;
	for (int i = 0; i < (int)TEX_PARAM::TEX_5 + 1; i++) {
		TEX_PARAM param = (TEX_PARAM)i;
		string desc = pMtrl->IsUsingTexParam(param);
		Ptr<CTexture> tex = pMtrl->GetTexParam(param);
		if ((desc[0] == 0 || desc == EMPTYSYMBOL) && tex.Get() == nullptr) continue;

		ImGui::Text(desc.c_str());
		ImGui::SameLine();

		string scalarKey = "##meshrenderTexKey" + to_string(i);

		// 텍스쳐 이미지 출력
		ImTextureID texid = nullptr;
		if (tex != nullptr) 
			texid = tex->GetSRV().Get();

		static bool use_text_color_for_tint = false;
		ImVec2 uv_max = ImVec2(1.0f, 1.0f);
		ImVec2 uv_min = ImVec2(0.0f, 0.0f);
		ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
		ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
		ImGui::Image(texid, ImVec2(150, 150), uv_min, uv_max, tint_col, border_col);

		texCnt++;
	}

	SetSize(ImVec2(0, 120 + scalarCnt * 22 + texCnt * 150));
}

void MeshRenderUI::MeshSelect(DWORD_PTR _ptr)
{
	string strMesh = (char*)_ptr;
	wstring strMeshName = ToWString(strMesh);

	Ptr<CMesh> pMesh = CAssetMgr::GetInst()->FindAsset<CMesh>(strMeshName);

	GetTargetObject()->MeshRender()->SetMesh(pMesh);
}

void MeshRenderUI::MaterialSelect(DWORD_PTR _ptr)
{
	string strMtrl = (char*)_ptr;
	wstring strMtrlName = ToWString(strMtrl);

	Ptr<CMaterial> pMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(strMtrlName);

	GetTargetObject()->MeshRender()->SetMaterial(pMtrl);
}
#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CMaterial.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>

#include "ParamUI.h"
#include "ListUI.h"

MaterialUI::MaterialUI()
	: AssetUI("Material", "##Material", ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}


void MaterialUI::render_update()
{
	AssetUI::render_update();

    // 해당 텍스쳐 이미지 출력
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    string strPath = string(pMtrl->GetRelativePath().begin(), pMtrl->GetRelativePath().end());

    ImGui::Text("Material");
    ImGui::SameLine();
    ImGui::InputText("##TexName", (char*)strPath.c_str(), strPath.length(), ImGuiInputTextFlags_ReadOnly);

    Ptr<CGraphicsShader> pShader = pMtrl->GetShader();
    string strShaderName;
    if (nullptr != pShader)
    {
        strShaderName = string(pShader->GetKey().begin(), pShader->GetKey().end());
    }

    ImGui::Text("Shader  ");
    ImGui::SameLine();
    ImGui::InputText("##ShaderName", (char*)strShaderName.c_str(), strShaderName.length(), ImGuiInputTextFlags_ReadOnly);

    // Mesh Drop 체크
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

        if (payload)
        {
            DWORD_PTR data = *((DWORD_PTR*)payload->Data);
            CAsset* pAsset = (CAsset*)data;
            if (ASSET_TYPE::GRAPHICS_SHADER == pAsset->GetType())
            {
                m_Mtrl->SetShader((CGraphicsShader*)pAsset);
            }
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::SameLine();
    if (ImGui::Button("##MtrlBtn", ImVec2(20, 20)))
    {
        // 리스트 UI
        ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

        vector<string> vecShaderName;
        CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::GRAPHICS_SHADER, vecShaderName);

        pListUI->AddString(vecShaderName);
        pListUI->SetDbClickDelegate(this, (Delegate_1)&MaterialUI::GraphicsShaderSelect);
        pListUI->Activate();
    }

    ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("Material Parameter");
    ImGui::Spacing(); ImGui::Spacing(); 

    // Shader Parameter
    if (nullptr == pShader)
        return;

    for (int i = 0; i < (int)SCALAR_PARAM::END; i++) {
        SCALAR_PARAM param = (SCALAR_PARAM)i;
        string desc = m_Mtrl->IsUsingScalarParam(param);

        string key = "##scalarparm" + std::to_string(i);
        switch ((SCALAR_PARAM)i)
        {
        case SCALAR_PARAM::INT_0:
        case SCALAR_PARAM::INT_1:
        case SCALAR_PARAM::INT_2:
        case SCALAR_PARAM::INT_3:
        {
            string intkey = "Int " + std::to_string(i % 4) + " Key";
            ImGui::Text(intkey.c_str()); ImGui::SameLine();
            ImGui::InputText(key.c_str(), desc.data(), 32);
            ParamUI::Param_INT((int*)pMtrl->GetScalarParam(param), desc);
        }
            break;
        case SCALAR_PARAM::FLOAT_0:
        case SCALAR_PARAM::FLOAT_1:
        case SCALAR_PARAM::FLOAT_2:
        case SCALAR_PARAM::FLOAT_3:
        {
            string floatkey = "Float " + std::to_string(i % 4) + " Key";
            ImGui::Text(floatkey.c_str()); ImGui::SameLine();
            ImGui::InputText(key.c_str(), desc.data(), 32);
            ParamUI::Param_FLOAT((float*)pMtrl->GetScalarParam(param), desc);
        }
            break;
        case SCALAR_PARAM::VEC2_0:
        case SCALAR_PARAM::VEC2_1:
        case SCALAR_PARAM::VEC2_2:
        case SCALAR_PARAM::VEC2_3:
        {
            string vec2key = "Vec2 " + std::to_string(i % 4) + " Key";
            ImGui::Text(vec2key.c_str()); ImGui::SameLine();
            ImGui::InputText(key.c_str(), desc.data(), 32);
            ParamUI::Param_VEC2((Vec2*)pMtrl->GetScalarParam(param), desc);
        }
            break;
        case SCALAR_PARAM::VEC4_0:
        case SCALAR_PARAM::VEC4_1:
        case SCALAR_PARAM::VEC4_2:
        case SCALAR_PARAM::VEC4_3:
        {
            string vec4key = "Vec4 " + std::to_string(i % 4) + " Key";
            ImGui::Text(vec4key.c_str()); ImGui::SameLine();
            ImGui::InputText(key.c_str(), desc.data(), 32);
            ParamUI::Param_VEC4((Vec4*)pMtrl->GetScalarParam(param), desc);
        }
            break;
        case SCALAR_PARAM::MAT_0:
        case SCALAR_PARAM::MAT_1:
        case SCALAR_PARAM::MAT_2:
        case SCALAR_PARAM::MAT_3:
            break;
        }
        m_Mtrl->SetUsingScalarParam(param, desc);
    }

    for (int i = 0; i < (int)TEX_PARAM::TEX_5 + 1; i++) {
        TEX_PARAM param = (TEX_PARAM)i;
        string desc = m_Mtrl->IsUsingTexParam(param);

        Ptr<CTexture> pTex = pMtrl->GetTexParam(param);
        string key = "##texparm" + std::to_string(i);

        string texkey = "Tex " + std::to_string(i) + " Key";
        ImGui::Text(texkey.c_str()); ImGui::SameLine();
        ImGui::InputText(key.c_str(), desc.data(), 32);
        if (ParamUI::Param_TEXTURE(pTex, desc, this, (Delegate_1)&MaterialUI::SelectTexture))
        {
            // 리스트 버튼을 눌렀다면
            m_SelectTexParam = param;
        }
        pMtrl->SetTexParam(param, pTex);
        m_Mtrl->SetUsingTexParam(param, desc);
    }
}

void MaterialUI::Activate()
{
    AssetUI::Activate();

    m_Mtrl = (CMaterial*)GetAsset().Get();
}

void MaterialUI::SelectTexture(DWORD_PTR _dwData)
{
    string strTex = (char*)_dwData;
    wstring strTexName = ToWString(strTex);

    Ptr<CTexture> pTex = CAssetMgr::GetInst()->FindAsset<CTexture>(strTexName);
    Ptr<CMaterial> pMtrl = (CMaterial*)GetAsset().Get();
    pMtrl->SetTexParam(m_SelectTexParam, pTex);    
}

void MaterialUI::GraphicsShaderSelect(DWORD_PTR _ptr)
{
    string strShader = (char*)_ptr;
    wstring strShaderName = ToWString(strShader);

    Ptr<CGraphicsShader> pShader = CAssetMgr::GetInst()->FindAsset<CGraphicsShader>(strShaderName);

    m_Mtrl->SetShader(pShader);
}

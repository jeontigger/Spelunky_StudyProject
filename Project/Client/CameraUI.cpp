#include "pch.h"
#include "CameraUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

CameraUI::CameraUI()
	: ComponentUI("Camera", UICameraName, COMPONENT_TYPE::CAMERA)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Activate()
{
	UI::Activate();

	m_camera = GetTargetObject()->Camera();
}

void CameraUI::render_update()
{
    ButtonTitle("Camera");

    ImGui::NewLine();
    static bool check = (bool)m_camera->GetProjType();
    if (ImGui::Checkbox("Orthographic", &check)) {
        if (check) {
            m_camera->SetProjType(PROJ_TYPE::PERSPECTIVE);
        }
        else {
            m_camera->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
        }
    }

    if (check) {
        static float fov = m_camera->GetFOV();
        if (ImGui::SliderFloat("FOV", &fov, 0.0f, XM_PI, "fov = %.3f")) {
            m_camera->SetFOV(fov);
        }
    }
    else {
        const char* ZoomType[] = { "Normal", "MapGenerating" };
        static int itype = 0;

        static float scale = m_camera->GetScale();
        if (ImGui::Combo("combo", &itype, ZoomType, IM_ARRAYSIZE(ZoomType))) {
            switch (itype)
            {
            case 0: 
                scale = CameraNormalScale;
                m_camera->SetScale(scale);
                break;

            case 1:
                scale = CameraMapGeneratingScale;
                m_camera->SetScale(scale);
                break;

            default:
                break;
            }
        }

        if (ImGui::SliderFloat("Scale", &scale, 0.1f, 10, "scale = %.3f")) {
            m_camera->SetScale(scale);
        }
    }

#define maxcol 4

    UINT layercheck = m_camera->GetLayerCheck();
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < maxcol; j++) {
            auto layer = CLevelMgr::GetInst()->GetCurrentLevel()->GetLayer(i* maxcol + j);
            if (layer == nullptr) continue;
            //if (layer->GetName() == L"") continue;
            string name = ToString(layer->GetName());
            if (name != L"") {
                name += "##nonamelayer";
            }
            name += std::to_string(i * maxcol + j);

            bool lc = layercheck >> (i * maxcol + j) & 1;
            if(ImGui::Checkbox(name.c_str(), &lc)){
                m_camera->LayerCheck(i * maxcol + j, lc);
            }
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

}

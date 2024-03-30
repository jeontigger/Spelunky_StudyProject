#include "pch.h"
#include "AnimationTool.h"

#include <Engine\CDevice.h>
#include <Engine\CPathMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CAssetMgr.h>
#include <Engine\Ptr.h>
#include <Engine\CAnim.h>

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CGameObject.h>
#include <Engine\CAnimator2D.h>

#pragma warning (disable: 4996)

AnimationTool::AnimationTool()
    : UI("AnimationTool", "##AnimationTool")
{
    //Deactivate();
    begin();
    SetSize(ImVec2(CDevice::GetInst()->GetRenderResolution().x, CDevice::GetInst()->GetRenderResolution().y));
    //SetModal(true);
    LoadAtlasPath(m_vecAtlasPaths);


}

AnimationTool::~AnimationTool()
{
}


void AnimationTool::LoadAtlasPath(vector<string>& vec)
{
    string path = ToString(CPathMgr::GetContentPath());
    path += "texture\\atlas\\";
    for (const auto& entry : fs::directory_iterator(path)) {
        string str = entry.path().string();
        str = str.substr(str.find("texture"));
        vec.push_back(str);
    }
}

void AnimationTool::MakeFrms()
{
    m_Frms.resize(m_vecLeftTops.size());
    for (size_t i = 0; i < m_Frms.size(); i++)
    {
        m_Frms[i].vSlice = Vec2(m_GridSize.x / m_ImgSize.x, m_GridSize.y / m_ImgSize.y);
        m_Frms[i].vLeftTop = Vec2(m_vecLeftTops[i].x / m_ImgSize.x, m_vecLeftTops[i].y / m_ImgSize.y);
        m_Frms[i].vOffset = Vec2(0, 0);
        m_Frms[i].vBackground = m_Frms[i].vSlice;
        m_Frms[i].Duration = 1.f / m_iFPS;
    }
}

bool AnimationTool::MakeAnim()
{

    CGameObject* obj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
    MakeFrms();
    if (m_Frms.size() != 0) {
        obj->Animator2D()->AddAnim(ToWString(m_nameBuffer), m_Atlas, m_Frms);
        obj->Animator2D()->Play(ToWString(m_nameBuffer));
    }
    else {
        return false;
    }
    return true;
}

void AnimationTool::PlayButton()
{
    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    if (ImGui::Button("Play")) {

        CGameObject* obj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

        // 애니메이션 크리에이트
        wstring key = ToWString(m_nameBuffer);
        key += std::to_wstring(m_iKeyIdx);
        MakeFrms();
        if (m_Frms.size() != 0) {
            obj->Animator2D()->AddAnim(key, m_Atlas, m_Frms);
            obj->Animator2D()->Play(key);
            m_iKeyIdx++;
        }

    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void AnimationTool::SaveButton()
{
    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    if (ImGui::Button("Save")) {

        CGameObject* obj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

        wstring animPath = CPathMgr::GetContentPath();
        animPath += L"anim\\";
        animPath += ToWString(m_nameBuffer);
        animPath += L".anim";

        if (m_vecLeftTops.size() == 0) {
            MessageBox(nullptr, L"프레임을 등록해주세요", L"애니메이션 저장", MB_OK);

            ImGui::PopStyleColor(3);
            ImGui::PopID();
            return;
        }

        if (m_nameBuffer[0] == '\0') {
            ImGui::PopStyleColor(3);
            ImGui::PopID();
            MessageBox(nullptr, L"애니메이션 이름을 지정해주세요", L"애니메이션 저장", MB_OK);
            return;
        }

        ofstream pFile;
        pFile.open(animPath);

        if (!pFile.is_open()) {
            MessageBox(nullptr, L"파일 열기 실패!", L"애니메이션 저장", MB_OK);
            assert(nullptr);
        }
        MakeAnim();
        CAnim* pAnim = obj->Animator2D()->GetCurAnim();
        pAnim->SetName(ToWString(m_nameBuffer));
        pAnim->SaveToFile(pFile);
        //m_Atlas->save
        MessageBox(nullptr, L"저장 완료!", L"애니메이션 저장", MB_OK);

    }

    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void AnimationTool::ClearButton()
{
    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    if (ImGui::Button("Clear")) {
        m_vecLeftTops.clear();
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void AnimationTool::LoadButton()
{
    ImGui::PushID(0);
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
    if (ImGui::Button("Load")) {
        wstring strLevelPath = CPathMgr::GetContentPath();
        strLevelPath += L"anim\\asdf.txt";

        FILE* pFile = nullptr;
        _wfopen_s(&pFile, strLevelPath.c_str(), L"rb");
        // 모든 프레임 정보 로드
        size_t FrmSize = 0;
        fread(&FrmSize, sizeof(size_t), 1, pFile);
        m_Frms.resize(FrmSize);
        fread(m_Frms.data(), sizeof(tAnimFrm), m_Frms.size(), pFile);

        m_obj->Animator2D()->AddAnim(strLevelPath, m_Atlas, m_Frms);
        m_obj->Animator2D()->Play(strLevelPath);
    }
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void AnimationTool::render_update()
{
    ButtonTitle("Select Atlas");

    VecCombo("## combo1", m_vecAtlasPaths, m_iComboIdx);
    if (m_vecAtlasPaths.size() == 0)
        return;

    static bool use_text_color_for_tint = false;
    // Atlas 그리기


    m_Atlas = CAssetMgr::GetInst()->Load<CTexture>(ToWString(m_vecAtlasPaths[m_iComboIdx]), ToWString(m_vecAtlasPaths[m_iComboIdx]));
    ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
    ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
    ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
    ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);
    int width = 800;
    int height = (float)m_Atlas.Get()->GetHeight() / m_Atlas.Get()->GetWidth() * width;
    m_ImgSize = { (float)width, (float)height };


    ButtonTitle("Grid Count");
    ImGui::InputInt2("##gridsize", m_vecGridCount.data());

    m_GridSize = m_ImgSize;
    m_GridSize.x /= m_vecGridCount[0];
    m_GridSize.y /= m_vecGridCount[1];

    ButtonTitle("FPS");
    ImGui::InputInt("##fps", &m_iFPS);

    ButtonTitle("Animation Name");
    ImGui::InputText("##animation name", m_nameBuffer, 32);

    static vector<float> mousepos = { 0, 0 };

    static vector<int> gridIdx = { 0, 0 };

    ImVec2 imagePos = ImGui::GetCursorScreenPos();
    ImGui::Image(m_Atlas->GetSRV().Get(), m_ImgSize, uv_min, uv_max, tint_col, border_col);
    // 마우스 클릭 감지
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
    {
        imagePos = ImGui::GetCursorScreenPos();
        ImVec2 mousePos = ImGui::GetMousePos();
        ImVec2 uv = (mousePos - imagePos) / m_ImgSize;
        mousepos = { uv.x, 1 + uv.y };
        gridIdx[0] = ((int)(mousepos[0] * m_vecGridCount[0]) % (int)m_GridSize[0]) * m_GridSize[0];
        gridIdx[1] = ((int)(mousepos[1] * m_vecGridCount[1]) % (int)m_GridSize[1]) * m_GridSize[1];
        m_vecLeftTops.emplace_back(gridIdx[0], gridIdx[1]);

        MakeFrms();
    }

    // 그리드 그리기
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImU32 gridColor = IM_COL32(255, 255, 255, 255);  // 그리드 색상 설정

    // 세로선 그리기
    for (int i = 0; i <= width; i += m_GridSize.x)
    {
        draw_list->AddLine(
            ImVec2(imagePos.x + i, imagePos.y),
            ImVec2(imagePos.x + i, imagePos.y + height),
            gridColor
        );
    }

    // 가로선 그리기
    for (int i = 0; i <= height; i += m_GridSize.y)
    {
        draw_list->AddLine(
            ImVec2(imagePos.x, imagePos.y + i),
            ImVec2(imagePos.x + width, imagePos.y + i),
            gridColor
        );
    }

    ImGui::SameLine();


    // 프레임 LeftTop 정보
    ImGui::BeginChild("LeftTops", ImVec2(200, 800), true, ImGuiWindowFlags_HorizontalScrollbar);

    ClearButton();

    ImGui::SameLine();
    PlayButton();

    ImGui::SameLine();
    SaveButton();

    ImGui::SameLine();
    LoadButton();

    ImGui::Separator();
    for (size_t i = 0; i < m_vecLeftTops.size(); i++)
    {
        string str = "";
        str += std::to_string(i);
        ButtonTitle(str.c_str());
        str = "##" + str;

        int lt[2] = { (float)m_vecLeftTops[i].x * m_Atlas->GetWidth() / 800, (float)m_vecLeftTops[i].y * m_Atlas->GetHeight() / 800 };
        ImGui::InputInt2(str.c_str(), lt);

        ImGui::SameLine();
        string name = "X##";
        name += std::to_string(i);
        if (ImGui::Button(name.c_str())) {
            m_vecLeftTops.erase(m_vecLeftTops.begin() + i);
            break;
        }
    }

    ImGui::EndChild();
    ImGui::SameLine();


    m_obj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
    CAnim* pAnim = m_obj->Animator2D()->GetCurAnim();
    if (pAnim != nullptr) {
        //ImGui::BeginChild("Animations", ImVec2(250, 250), true, ImGuiWindowFlags_HorizontalScrollbar);

        tAnimFrm frm = pAnim->GetCurFrm();
        ImGui::Image(m_Atlas->GetSRV().Get(), { 200, 200 }, { frm.vLeftTop.x, frm.vLeftTop.y }, { frm.vLeftTop.x + frm.vSlice.x, frm.vLeftTop.y + frm.vSlice.y }, tint_col, border_col);

        //ImGui::EndChild();
    }

}

void AnimationTool::Activate()
{
    UI::Activate();
    begin();
}

void AnimationTool::begin()
{
    m_vecGridCount.clear();
    m_vecGridCount = { 16, 16 };
    m_vecLeftTops.clear();
    m_Frms.clear();

    m_iFPS = 16;

    m_iComboIdx = 0;

}

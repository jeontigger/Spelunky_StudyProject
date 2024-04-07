#include "pch.h"
#include "MenuUI.h"



#include <Engine/CPathMgr.h>
#include <Engine/CTaskMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "CLevelSaveLoad.h"
#include "CLevelGenerator.h"

MenuUI::MenuUI()
	: UI("Menu", "##Menu")
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::render()
{
    if (ImGui::BeginMainMenuBar())
    {     
        render_update();

        ImGui::EndMainMenuBar();
    }
}

void MenuUI::render_update()
{
    File();

    Window();

    Level();

    Animation();

    TileMaker();

    GameObject();
    
    Asset();
}

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Save Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetSaveFileName(&ofn))
            {                
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurrentLevel(), CPathMgr::GetRelativePath(szSelect));
            }
        }

        if (ImGui::MenuItem("Load Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {                
                CLevel* pLevel = CLevelSaveLoad::LoadLevel(CPathMgr::GetRelativePath(szSelect));
                CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);

                // Inspector 의 타겟정보를 nullptr 로 되돌리기
                Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                pInspector->SetTargetObject(nullptr);
            }
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Window()
{
    if (ImGui::BeginMenu("Window"))
    {
        UI* content = UIMGR->FindUI(UIContentName);
        UI* inspector = UIMGR->FindUI(UIInspectorName);
        UI* outliner = UIMGR->FindUI(UIOutlinerName);
        if (ImGui::MenuItem("Content", nullptr, nullptr, !content->IsActivate()))
        {
            content->Activate();
        }

        if (ImGui::MenuItem("Inspector", nullptr, nullptr, !inspector->IsActivate()))
        {
            inspector->Activate();
        }

        if (ImGui::MenuItem("Outliner", nullptr, nullptr, !outliner->IsActivate()))
        {
            outliner->Activate();
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

        LEVEL_STATE State = pCurLevel->GetState();

        bool PlayEnable = false;
        bool PauseEnable = false;
        bool StopEnable = false;

        if (LEVEL_STATE::STOP == State || LEVEL_STATE::PAUSE == State)
            PlayEnable = true;
        else
            PlayEnable = false;

        if (LEVEL_STATE::PLAY == State)
            PauseEnable = true;
        else
            PauseEnable = false;

        if (LEVEL_STATE::PLAY == State || LEVEL_STATE::PAUSE == State)
            StopEnable = true;
        else
            StopEnable = false;

        
        if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
        {
            CLevel* level = nullptr;
            if (LEVEL_STATE::STOP == pCurLevel->GetState())
            {
                level = (CLevel*)CLevelGenerator::LoadLevels(0);
            }
            
            CLevelMgr::GetInst()->ChangeLevel(level, LEVEL_STATE::PLAY);
        }

        if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
        {
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PAUSE);
        }

        if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
        {
            //CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//temp.lv");
            CLevelGenerator::LoadTempLevel();

            // Inspector 의 타겟정보를 nullptr 로 되돌리기
            Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
            pInspector->SetTargetObject(nullptr);
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Animation()
{
    UI* aniTool = UIMGR->FindUI(UIAnimationToolName);
    if (aniTool && ImGui::MenuItem("AnimationTool", nullptr, nullptr, true))
    {
        if (aniTool->IsActivate()) {
            UIMGR->UIDeactivate(UIAnimationToolName);
        }
        else {
            UIMGR->UIActivate(UIAnimationToolName);
        }
        
    }
}

void MenuUI::TileMaker()
{
    UI* tilemaker = UIMGR->FindUI(UITileMakerName);
    if (tilemaker && ImGui::MenuItem("TileMaker", nullptr, nullptr, true))
    {
        if (tilemaker->IsActivate()) {
            UIMGR->UIDeactivate(UITileMakerName);
        }
        else {
            UIMGR->UIActivate(UITileMakerName);
        }

    }
}


void MenuUI::GameObject()
{
    if (ImGui::MenuItem("Create Empty Object", ""))
    {
        CGameObject* pNewObj = new CGameObject;
        pNewObj->SetName(L"New GameObject");
        pNewObj->AddComponent(new CTransform);
        GamePlayStatic::SpawnGameObject(pNewObj, 0);
    }
}

void MenuUI::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::MenuItem("Create Empty Material"))
        {
            wchar_t szPath[255] = {};
            wstring FilePath = CPathMgr::GetContentPath();

            int num = 0;
            while (true)
            {
                swprintf_s(szPath, L"Material//New Material_%d.mtrl", num);
                if (!exists(FilePath + szPath))
                    break;
                ++num;
            }

            CMaterial* pMtrl = new CMaterial;
            pMtrl->SetName(szPath);
            pMtrl->Save(szPath);
            GamePlayStatic::AddAsset(pMtrl);
        }
        if (ImGui::MenuItem("Create Empty FSM"))
        {
            wchar_t szPath[255] = {};
            wstring FilePath = CPathMgr::GetContentPath();

            int num = 0;
            while (true)
            {
                swprintf_s(szPath, L"fsm//NewFSM_%d.fsm", num);
                if (!exists(FilePath + szPath))
                    break;
                ++num;
            }

            CFSM* pFSM = new CFSM;
            pFSM->SetName(szPath);
            pFSM->Save(szPath);
            GamePlayStatic::AddAsset(pFSM);
        }
        ImGui::EndMenu();
    }
}


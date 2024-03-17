#pragma once
#include "UI.h"
#include <Engine\CAnim.h>

class AnimationTool :
    public UI
{
private:
    vector<string> m_vecAtlasPaths;
    vector<int> m_vecGridCount;
    vector<ImVec2> m_vecLeftTops;
    vector<tAnimFrm> m_Frms;

    ImVec2 m_GridSize;
    ImVec2 m_ImgSize;
    Ptr<CTexture> m_Atlas;
    class CGameObject* m_obj;

    char m_nameBuffer[32];

    int m_iFPS;
    int m_iComboIdx;

    int m_iKeyIdx = 0;

public:
    virtual void render_update()override;
    virtual void Activate() override;
    virtual void begin() override;

public:
    AnimationTool();
    ~AnimationTool();

private:
    void ButtonTitle(const char* Content);
    void VecCombo(const char* ID, const vector<string>& vec, int& i);
    void LoadAtlasPath(vector<string>& vec);
    void MakeFrms();
    bool MakeAnim();

    void ClearButton();
    void PlayButton();
    void SaveButton();
    void LoadButton();
};


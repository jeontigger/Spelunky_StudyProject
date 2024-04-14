#pragma once
#include <Engine\CLevel.h>

enum class TitleLevelState {
    AnyKeyPress,
    Select,
};

enum class TitleMenu {
    GameStart,
    Quit,
    END,
};

#define CursorHidePosX -620
#define CursorSelectPosX -422
#define CursorStartPosY 0
#define CursorYSpaceSize 80
class CTitleLevel :
    public CLevel
{
private:
    TitleLevelState m_State;

    CGameObject* m_MainCamera;

    vector<CGameObject*> m_vecAnyKeyObj;
    vector<CGameObject*> m_vecSelectObj;

    int m_iMenuCursor;
    CGameObject* m_arrCursors[(UINT)TitleMenu::END];    

    void (*ChangeLevel)(void);

private:
    wstring m_strStart;
    wstring m_strMenuStart;
    wstring m_strMenuQuit;

public:
    void SetLevelChangeFunc(void (*func)(void)) { ChangeLevel = func; }

public:
    virtual void tick() override;
    virtual void begin() override;

public:
    CTitleLevel();
    ~CTitleLevel();

private:
    void ChangeLevelState(TitleLevelState _state);

private:
    void AnyKeyObjectsInit();
    void SelectObjectInit();
    void CursorMove();
    void CursorControl();
    void MenuSelect();
    void MenuStringPrint();
};


#pragma once
#include <Engine/CLevel.h>
#include "CTileBlock.h"

enum class StageState {
    NONE,
    CREATE_BLOCK,
    SELECT_ENTRANCE,
    SELECT_EXIT,
    GENERATE_PATH,
    ATTACH_TILEBLOCK,
    REGIST_BACKGROUND,
    TILE_INSTANCING,
    MONSTER_GENERATING,
    PLAYER_SETTING,
    END,
};

class CStage :
    public CLevel
{
private:
    CGameObject* m_Player;
    CGameObject* m_MainCamera;

    // 시각화용
private:
    StageState m_state;
    vector<vector<class CGameObject*>> m_vecBackgrounds;
    int m_iEntrancePos;
    int m_iExitPos;

private:
    bool m_visited[STAGETILEROW][STAGETILECOL];
    vector<Vec2> m_Path;
    class CStagePack* m_SP;

    CTileBlock m_arrTileBlocks[STAGETILEROW][STAGETILECOL];


public:
    void SetStagePack(CStagePack* _sp) { m_SP = _sp; };

public:
    virtual void tick() override;
    virtual void finaltick() override;
    virtual void begin() override;

public:
    CStage();
    ~CStage();

private:
    void ChangeState(StageState _state);
    void CreateBlocks();
    void SelectEntrance();
    void SelectExit();
    void GeneratePath();
    void DFSGenerate(vector<Vec2>& _path, bool find);
    void FitType();
    void SelectBlock();
    void RegistBackground();
    void TileInstancing();
    void MonsterGenerating();
    void PlayerSetting();

private:
    void PrintChangeState(const wchar_t* _content);
    void PathVisualization();
};
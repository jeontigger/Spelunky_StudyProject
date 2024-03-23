#pragma once
#include <Engine/CLevel.h>
#include "CTileBlock.h"

enum class StageState {
    NONE,
    CREATE_BLOCK,
    GENERATE_PATH,
    ATTACH_TILEBLOCK,
    TILE_INSTANCING,
    END,
};

class CStage :
    public CLevel
{
    // 시각화용
private:
    StageState m_state;
    vector<class CGameObject> m_vecBlocks;

private:
    class CStagePack* m_SP;

    CTileBlock m_arrTileBlocks[STAGETILEROW][STAGETILECOL];


public:
    void SetStagePack(CStagePack* _sp) { m_SP = _sp; };

public:
    virtual void tick() override;
    virtual void finaltick() override;

public:
    CStage();
    ~CStage();

private:
    void ChangeState(StageState _state);
    void CreateBlocks();
};


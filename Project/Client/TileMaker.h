#pragma once
#include "UI.h"

#include <Scripts/CTileBlock.h>

enum class TileMakerState {
    NONE,
    New,
    Modify,
    END,
};

class TileMaker :
    public UI
{
private:
    class CStage* m_newStage;
    class CTileBlock* m_newTileBlock;
    BlockTileType m_curType;

    class CStage* m_curStage;
    class CTileBlock* m_curTileBlock;

    vector<string> m_StageNames;
    vector<class CStage> m_vecStages;

    TileMakerState m_state;

    char m_StageName[32];

    Ptr<CTexture> m_texBlockTile;
private:
    void ReturnButton();
    void LoadAllStages();

    void TileBlockMenu();

public:
    virtual void render_update() override;

public:
    TileMaker();
    ~TileMaker();

};


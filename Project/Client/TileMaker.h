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
    vector<vector<CTileBlock*>> m_vecTileBlocks;
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
    void PrintTileBlock(CTileBlock* _tileblock);
    void PrintStageBlocks();
    void LoadStageBlock(int type, int idx);
    void DeleteStageBlock(int type, int idx);
    void SortTileBlocks(CStage* _stage);

public:
    virtual void render_update() override;

public:
    TileMaker();
    ~TileMaker();

};


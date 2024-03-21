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
    class CTileBlock m_newTileBlock;

    vector<vector<CTileBlock>> m_vecNewTileBlocks;
    vector<vector<CTileBlock>> m_vecTileBlocks;

    int m_iTypeCursor;
    BlockTileType m_curType;

    class CStage* m_curStage;
    class CTileBlock m_curTileBlock;

    vector<string> m_StageNames;
    vector<class CStage*> m_vecStages;

    TileMakerState m_state;

    char m_StageName[32];

    Ptr<CTexture> m_texBlockTile;


private:
    void ReturnButton();
    void NewStageSaveButton();
    void LoadAllStages();

    void TileBlockMenu(vector<vector<CTileBlock>>& vvec);
    void PrintTileBlock(CTileBlock& _tileblock);
    void PrintStageBlocks(vector<vector<CTileBlock>>& vvec);
    void LoadStageBlock(vector<vector<CTileBlock>> vvec, int type, int idx);
    void DeleteStageBlock(vector<vector<CTileBlock>>& vvec, int type, int idx);
    void SortTileBlocks(CStage* _stage);

    void SaveStage(CStage* _stage, vector<vector<CTileBlock>> _vvec);
    void SaveStage(CStage* _stage, vector<vector<CTileBlock>> _vvec, int _num);

    void FillTileBlocks(CStage* _stage, vector<vector<CTileBlock>> _vvec);

private:
    void ClearTileBlocks(vector<vector<CTileBlock>>& _blocks);

public:
    virtual void render_update() override;

public:
    TileMaker();
    ~TileMaker();

};


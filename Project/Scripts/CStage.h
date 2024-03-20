#pragma once
#include <Engine/CLevel.h>

#include "CTileBlock.h"

class CStage :
    public CLevel
{
private:

    /// <summary>
    /// 생성된 타일 블럭들
    /// </summary>
    vector<vector<CTileBlock>> m_TileBlocks;
    Ptr<CTexture> m_texBackground;

    /// <summary>
    /// 생성시키기 위한 타일 리스트
    /// </summary>
    map<TileBlockType, vector<CTileBlock>> m_mapBlockList;

public:
    void AddTileBlock(TileBlockType _type, CTileBlock _block);
    inline map<TileBlockType, vector<CTileBlock>> GetList() { return m_mapBlockList; }

    friend ifstream& operator>>(ifstream& fin, CStage& stage);
    friend ofstream& operator<<(ofstream& fout, const CStage& stage);
public:
    CStage();
    ~CStage();
};


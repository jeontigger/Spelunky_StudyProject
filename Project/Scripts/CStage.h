#pragma once
#include <Engine/CLevel.h>

#include "CTileBlock.h"

class CStage :
    public CLevel
{
private:

    /// <summary>
    /// ������ Ÿ�� ����
    /// </summary>
    vector<vector<CTileBlock>> m_TileBlocks;
    Ptr<CTexture> m_texBackground;

    /// <summary>
    /// ������Ű�� ���� Ÿ�� ����Ʈ
    /// </summary>
    map<TileBlockType, CTileBlock*> m_mapBlockList;

public:
    void AddTileBlock(TileBlockType _type, CTileBlock* _block);
    inline map<TileBlockType, CTileBlock*> GetList() { return m_mapBlockList; }

public:
    CStage();
    ~CStage();
};


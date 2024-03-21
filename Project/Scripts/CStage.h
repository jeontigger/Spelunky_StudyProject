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
    map<TileBlockType, vector<CTileBlock>> m_mapBlockList;

public:
    void SetBackground(Ptr<CTexture> _bg) { m_texBackground = _bg; }
    Ptr<CTexture> GetBackground() { return m_texBackground; }

public:
    inline void ClearTileBlock(TileBlockType _type) { m_mapBlockList[_type].clear(); }
    void AddTileBlock(TileBlockType _type, CTileBlock _block);
    inline map<TileBlockType, vector<CTileBlock>> GetList() { return m_mapBlockList; }

    friend ifstream& operator>>(ifstream& fin, CStage& stage);
    friend ofstream& operator<<(ofstream& fout, const CStage& stage);
public:
    CStage();
    ~CStage();
};


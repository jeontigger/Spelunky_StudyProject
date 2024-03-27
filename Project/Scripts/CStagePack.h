#pragma once
#include <Engine/CEntity.h>

#include "CTileBlock.h"
#include "CTileChunk.h"

class CStagePack :
    public CEntity
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
    map<ChunkType, vector<CTileChunk>> m_mapChunkList;

public:
    void SetBackground(Ptr<CTexture> _bg) { m_texBackground = _bg; }
    Ptr<CTexture> GetBackground() { return m_texBackground; }
    CTileBlock GetRandomBlock(TileBlockType _type);
    CTileChunk GetRandomChunk(ChunkType _type);

public:
    inline void ClearTileBlock(TileBlockType _type) { m_mapBlockList[_type].clear(); }
    void AddTileBlock(TileBlockType _type, CTileBlock _block);
    inline const map<TileBlockType, vector<CTileBlock>>& GetList() { return m_mapBlockList; }
    inline const map<ChunkType, vector<CTileChunk>>& GetChunks() { return m_mapChunkList; }

    friend ifstream& operator>>(ifstream& fin, CStagePack& stage);
    friend ofstream& operator<<(ofstream& fout, const CStagePack& stage);
public:
    CLONE_DISABLE(CStagePack);

    CStagePack();
    ~CStagePack();
};


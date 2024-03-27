#include "pch.h"
#include "CStagePack.h"

#include "CTileBlock.h"

#include "CRandomMgr.h"

CStagePack::CStagePack()
{
	m_TileBlocks.resize(STAGETILEROW);
	for (int row = 0; row < STAGETILEROW; row++) {
		m_TileBlocks[row].resize(STAGETILECOL);
	}
}

CStagePack::~CStagePack()
{

}

CTileBlock CStagePack::GetRandomBlock(TileBlockType _type)
{
	const vector<CTileBlock> blocks = m_mapBlockList[_type];
	int random = GETRANDOM(blocks.size());

	return m_mapBlockList[_type][random];
}

CTileChunk CStagePack::GetRandomChunk(ChunkType _type)
{
	const vector<CTileChunk> blocks = m_mapChunkList[_type];
	int random = GETRANDOM(blocks.size());

	return m_mapChunkList[_type][random];
}

void CStagePack::AddTileBlock(TileBlockType _type, CTileBlock _block)
{
	m_mapBlockList[_type].push_back(_block);
}

ifstream& operator>>(ifstream& fin,  CStagePack& stage)
{
	LoadAssetRef(stage.m_texBackground, fin);
	int type;
	while (fin >> type) {
		CTileBlock tileblock;
		fin >> tileblock;
		tileblock.SetBlockType((TileBlockType)type);
		stage.AddTileBlock((TileBlockType)type, tileblock);
	}

	{
		wstring path = CPathMgr::GetContentPath();
		path += ChunkPath;
		ifstream fin(path);
		int num;
		fin >> num;
		for (int i = 0; i < num; i++) {
			CTileChunk chunk;
			int type;
			fin >> type;
			fin >> chunk;
			chunk.SetType((ChunkType)type);
			stage.m_mapChunkList[(ChunkType)type].push_back(chunk);
		}
	}

	return fin;
}

ofstream& operator<<(ofstream& fout, const CStagePack& stage)
{
	SaveAssetRef(stage.m_texBackground, fout);

	auto map = stage.m_mapBlockList;
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		
		auto vec = iter->second;
		for (int i = 0; i < vec.size(); i++) {
			fout <<(int)iter->first << endl;
			fout << vec[i] << endl << endl;
		}
	}
	return fout;
}

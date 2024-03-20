#include "pch.h"
#include "CStage.h"

#include "CTileBlock.h"

CStage::CStage()
{
	m_TileBlocks.resize(STAGETILEROW);
	for (int row = 0; row < STAGETILEROW; row++) {
		m_TileBlocks[row].resize(STAGETILECOL);
	}
}

CStage::~CStage()
{
	Delete_Map(m_mapBlockList);
}

void CStage::AddTileBlock(TileBlockType _type, CTileBlock* _block)
{
	m_mapBlockList[_type] = _block;
}

ofstream& operator<<(ofstream& fout, const CStage& stage)
{
	auto map = stage.m_mapBlockList;
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		fout << TileBlockTypeStrings[(int)iter->first] << endl;
		fout << *(iter->second) << endl;
	}
	return fout;
}

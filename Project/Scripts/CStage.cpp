#include "pch.h"
#include "CStage.h"


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
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
}

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
	for (auto iter = m_mapBlockList.begin(); iter != m_mapBlockList.end(); ++iter) {
		auto vec = iter->second;
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i])
				delete vec[i];
		}
	}
}

void CStage::AddTileBlock(TileBlockType _type, CTileBlock* _block)
{
	m_mapBlockList[_type].push_back(_block);
}

ofstream& operator<<(ofstream& fout, const CStage& stage)
{
	auto map = stage.m_mapBlockList;
	for (auto iter = map.begin(); iter != map.end(); ++iter) {
		
		auto vec = iter->second;
		for (int i = 0; i < vec.size(); i++) {
			fout << TileBlockTypeStrings[(int)iter->first] << endl;
			fout << *vec[i] << endl << endl;
		}
	}
	return fout;
}

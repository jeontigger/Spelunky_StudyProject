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

void CStage::AddTileBlock(TileBlockType _type, CTileBlock _block)
{
	m_mapBlockList[_type].push_back(_block);
}

ifstream& operator>>(ifstream& fin,  CStage& stage)
{
	int type;
	while (fin >> type) {
		CTileBlock tileblock;
		fin >> tileblock;
		stage.AddTileBlock((TileBlockType)type, tileblock);
	}

	return fin;
}

ofstream& operator<<(ofstream& fout, const CStage& stage)
{
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

#include "pch.h"

#include "CTileBlock.h"

CTileBlock::CTileBlock()
	: m_Type(TileBlockType::NONE)
{
	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			m_Tiles[row][col] = BlockTileType::Blank;
		}
	}
}

CTileBlock::~CTileBlock()
{
}

void CTileBlock::Save(ofstream& fout)
{
	fout << (int)m_Type << endl;
	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			fout << (int)m_Tiles[row][col] << " ";
		}
		fout << endl;
	}
}

void CTileBlock::Load(ifstream& fin)
{
	int type;
	fin >> type;
	m_Type = (TileBlockType)type;

	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			fin >> type;
			m_Tiles[row][col] = (BlockTileType(type));
		}
	}
}

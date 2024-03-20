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

ofstream& operator<<(ofstream& fout, const CTileBlock& tileblock)
{
	for (int row = 0; row < TILEBLOCKSIZE; row++) {
		for (int col = 0; col < TILEBLOCKSIZE; col++) {
			fout << (int)tileblock.m_Tiles[row][col] << " ";
		}
		fout << endl;
	}
	return fout;
}

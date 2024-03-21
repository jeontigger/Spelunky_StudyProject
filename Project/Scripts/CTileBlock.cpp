#include "pch.h"

#include "CTileBlock.h"

CTileBlock::CTileBlock()
	: m_Type(TileBlockType::NONE)
{
	for (int row = 0; row < TILEBLOCKSIZEY; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			m_Tiles[row][col] = BlockTileType::Blank;
		}
	}
}

CTileBlock::~CTileBlock()
{
}

ifstream& operator>>(ifstream& fin, CTileBlock& tileblock)
{
	int num;
	for (int row = 0; row < TILEBLOCKSIZEY; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			fin >> num;
			tileblock.SetTileType((BlockTileType)num, row, col);
		}
	}
	return fin;
}

ofstream& operator<<(ofstream& fout, const CTileBlock& tileblock)
{
	for (int row = 0; row < TILEBLOCKSIZEY; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			fout << (int)tileblock.m_Tiles[row][col] << " ";
		}
		fout << endl;
	}
	return fout;
}

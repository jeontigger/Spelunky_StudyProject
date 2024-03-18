#include "pch.h"

#include "CTileBlock.h"

CTileBlock::CTileBlock()
	: m_Type(TileBlockType::NONE)
{
	for (int i = 0; i < TILEBLOCKSIZE * TILEBLOCKSIZE; i++) {
		Vec2 pos = math::IdxToRowCol(i, Vec2(TILEBLOCKSIZE, TILEBLOCKSIZE));
		m_Tiles[(int)pos.x][(int)pos.y] = BlockTileType::Blank;
	}

}

CTileBlock::~CTileBlock()
{
}

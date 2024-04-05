#include "pch.h"
#include "CTileMgr.h"

#include "CTile.h"

void CTileMgr::SetTile(CGameObject* tile, int _blockRow, int _blockCol, int _tileRow, int _tileCol)
{
	m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol] = tile;
}

CTile* CTileMgr::GetTile(Vec2 _idx)
{
	int blockRow = _idx.y / STAGETILEROW;
	int blockCol = _idx.x / STAGETILECOL;
	int tileRow = (int)_idx.y % TILEBLOCKSIZEY;
	int tileCol = (int)_idx.x % TILEBLOCKSIZEX;

	return m_arrTiles[blockRow][blockCol][tileRow][tileCol]->GetScript<CTile>();
}

CTile* CTileMgr::GetTile(int _blockRow, int _blockCol, int _tileRow, int _tileCol)
{
	if (_tileRow >= TILEBLOCKSIZEY) {
		_blockRow += _tileRow / TILEBLOCKSIZEY;
		_tileRow = _tileRow % TILEBLOCKSIZEY;
	}
	if (_tileCol >= TILEBLOCKSIZEX) {
		_blockCol += _tileCol / TILEBLOCKSIZEX;
		_tileCol = _tileCol % TILEBLOCKSIZEX;
	}
	if (m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol]) {
		return m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol]->GetScript<CTile>();
	}
	return nullptr;
}

Vec2 CTileMgr::PosToIdx(Vec3 _vPos)
{
	return Vec2((int)_vPos.x / TileScaleX, (int)_vPos.y / TileScaleY);
}

Vec3 CTileMgr::IdxToPos(Vec2 _Idx)
{
	return Vec3((0.5f + _Idx.x) * TileScaleX, -(0.5f + _Idx.y) * TileScaleY, 0.f);
}

Vec3 CTileMgr::IdxToPos(int _BlockRow, int _BlockCol, int _TileRow, int _TileCol)
{
	return IdxToPos(Vec2(_BlockCol * TILEBLOCKSIZEX + _TileCol, _BlockRow * TILEBLOCKSIZEY + _TileRow));
}

CTileMgr::CTileMgr()
{
	for (int blockrow = 0; blockrow < STAGETILEROW; blockrow++) {
		for (int blockcol = 0; blockcol < STAGETILECOL; blockcol++) {
			for (int row = 0; row < TILEBLOCKSIZEY; row++) {
				for (int col = 0; col < TILEBLOCKSIZEX; col++) {
					m_arrTiles[blockrow][blockcol][row][col] = nullptr;
				}
			}
		}
	}
}

CTileMgr::~CTileMgr()
{
}

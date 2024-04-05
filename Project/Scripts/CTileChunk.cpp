#include "pch.h"
#include "CTileChunk.h"

#include "CTile.h"
#include "CRandomMgr.h"
#include "CTileMgr.h"

CTileChunk::CTileChunk()
{
}

CTileChunk::~CTileChunk()
{
}

void CTileChunk::Init(int _row, int _col)
{
	m_row = _row;
	m_col = _col;

	m_Tiles.clear();

	m_Tiles.resize(_row);
	m_row = _row;
	m_col = _col;
	for (int row = 0; row < _row; row++) {
		m_Tiles[row].clear();
		m_Tiles[row].resize(_col);
	}
}

void CTileChunk::SetTileType(BlockTileType type, int row, int col)
{
	if (0 <= row && row < m_row && 0 <= col && col < m_col) {
		m_Tiles[row][col] = type;
	}
}

void CTileChunk::Instancing(int _StageRow, int _StageCol, int _BlockRow, int _BlockCol)
{
	auto tilepref = CAssetMgr::GetInst()->Load<CPrefab>(TilePrefKey, TilePrefKey);
	for (int row = 0; row < m_row; row++) {
		for (int col = 0; col < m_col; col++) {
			auto tile = tilepref->Instantiate();
			auto script = tile->GetScript<CTile>();
			TileType tiletype = TileType::Blank;
			switch (m_Tiles[row][col])
			{
			case BlockTileType::Blank:
				break;
			case BlockTileType::Soil:
				tiletype = TileType::Soil;
				break;
			case BlockTileType::Soil_50:
				if (GETRANDOM(2) == 0) {
					tiletype = TileType::Blank;
				}
				else {
					tiletype = TileType::Soil;
				}
				break;
			case BlockTileType::Tree:
				tiletype = TileType::Tree;
				break;
			case BlockTileType::NeverCrash:
				tiletype = TileType::NeverCrash;
				break;
			case BlockTileType::Ladder:
				tiletype = TileType::Ladder;
				break;
			case BlockTileType::LadderHalf:
				tiletype = TileType::LadderHalf;
				break;
			case BlockTileType::Half:
				tiletype = TileType::Half;
				break;
			case BlockTileType::END:
				break;
			default:
				break;
			}
			if (tiletype == TileType::Blank) {
				delete tile;
			}
			else {
				script->SetTileType(tiletype);
				Vec3 vPos(_StageCol * TileBlockScaleX + (0.5f + _BlockCol + col) * TileScaleX, -_StageRow * TileBlockScaleY - (0.5f + _BlockRow + row) * TileScaleY, TileZ);
				tile->Transform()->SetRelativePos(vPos);
				CTileMgr::GetInst()->SetTile(tile, _StageRow, _StageCol, _BlockRow, _BlockCol);
				GamePlayStatic::SpawnGameObject(tile, TileEmergencyLayer);
			}
		}
	}
}

ofstream& operator<<(ofstream& fout, CTileChunk& chunk)
{
	fout << (int)chunk.m_Type << endl;
	fout << chunk.m_row << " " << chunk.m_col << endl;
	for (int row = 0; row < chunk.m_row; row++) {
		for (int col = 0; col < chunk.m_col; col++) {
			fout << (int)chunk.m_Tiles[row][col] << " ";
		}
		fout << endl;
	}

	return fout;
}

ifstream& operator>>(ifstream& fin, CTileChunk& chunk)
{
	fin >> chunk.m_row >> chunk.m_col;
	chunk.m_Tiles.resize(chunk.m_row);
	for (int row = 0; row < chunk.m_row; row++) {
		chunk.m_Tiles[row].resize(chunk.m_col);
		for (int col = 0; col < chunk.m_col; col++) {
			int type;
			fin >> type;
			chunk.m_Tiles[row][col] = (BlockTileType)type;
		}
	}

	return fin;
}

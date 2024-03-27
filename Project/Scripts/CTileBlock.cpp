#include "pch.h"

#include "CTileBlock.h"
#include "CTile.h"
#include <Engine/CGameObject.h>

#include "CRandomMgr.h"
#include "CStagePackMgr.h"

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

void CTileBlock::TileInstancing(int _row, int _col)
{
	auto tilepref = CAssetMgr::GetInst()->Load<CPrefab>(TilePrefKey, TilePrefKey);
	for (int row = 0; row < TILEBLOCKSIZEY; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			int rowpos = _row + TileScaleY * (TILEBLOCKSIZEY / 2) - TileScaleY / 2 - row * TileScaleY;
			int colpos = _col + TileScaleX * (TILEBLOCKSIZEX / 2) - TileScaleX / 2 - col * TileScaleX;

			auto type = m_Tiles[row][col];
			auto tile = tilepref->Instantiate();
			auto script = tile->GetScript<CTile>();
			TileType tiletype = TileType::Blank;
			switch (type)
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
				tiletype = TileType::Blank;
				break;
			case BlockTileType::Movable:
				tiletype = TileType::Movable;
				break;
			case BlockTileType::Spike:
				tiletype = TileType::Spike;
				break;
			case BlockTileType::ChunkGround:
			{
				CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
				auto chunk = sp->GetRandomChunk(ChunkType::Ground);
				chunk.Instancing(colpos, rowpos);
			}
				break;
			case BlockTileType::ChunkAir:
			{

			}
				break;
			case BlockTileType::ChunkDoor:
			{

			}
				tiletype = TileType::Blank;
				break;
			case BlockTileType::END:
				tiletype = TileType::Blank;
				break;
			default:
				tiletype = TileType::Blank;
				break;
			}

			if (tiletype == TileType::Blank) {
				delete tile;
			}
			else {
				script->Instancing(tiletype, colpos, rowpos);
				GamePlayStatic::SpawnGameObject(tile, TileLayer);
			}

			
		}
	}
}
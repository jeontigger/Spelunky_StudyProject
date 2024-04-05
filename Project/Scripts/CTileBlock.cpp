#include "pch.h"

#include "CTileBlock.h"
#include "CTile.h"
#include <Engine/CGameObject.h>

#include "CRandomMgr.h"
#include "CStagePackMgr.h"
#include "CTileMgr.h"

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
				tiletype = TileType::Half;
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
				chunk.Instancing(_row, _col, row, col);
			}
				break;
			case BlockTileType::ChunkAir:
			{
				CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
				auto chunk = sp->GetRandomChunk(ChunkType::Air);
				chunk.Instancing(_row, _col, row, col);
			}
				break;
			case BlockTileType::ChunkDoor:
			{
				tiletype = TileType::Door;
				script->SetTileType(tiletype);
				tile->Transform()->SetRelativePos(Vec3(_col * TileBlockScaleX + (0.5f + col) * TileScaleX, -_row * TileBlockScaleY - (1.f + row) * TileScaleY, TileZ));
				tile->Transform()->SetRelativeScale(Vec3(TileScaleX * 3, TileScaleY * 2, 1));
				tile->Collider2D()->SetOffsetScale(Vec2(0.33f, 0.5f));
				tile->Collider2D()->SetOffsetPos(Vec2(0.f, -0.25f));
				CTileMgr::GetInst()->SetTile(tile, _row, _col, row, col);
				GamePlayStatic::SpawnGameObject(tile, TileEmergencyLayer);
			}
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
			else if(tiletype != TileType::Door){
				script->SetTileType(tiletype);
				tile->Transform()->SetRelativePos(Vec3(_col * TileBlockScaleX + (0.5f + col) * TileScaleX, -_row * TileBlockScaleY - (0.5f + row) * TileScaleY, TileZ));
				CTileMgr::GetInst()->SetTile(tile, _row, _col, row, col);
				GamePlayStatic::SpawnGameObject(tile, TileEmergencyLayer);
			}
		}
	}
}

#include "CFieldObject.h"
void CTileBlock::MonsterGenerating(int _row, int _col)
{
	auto idx = CTileMgr::GetInst()->PosToIdx(Vec3(1.f, 129.f, 0));

	for (int row = 0; row < TILEBLOCKSIZEY - 1; row++) {
		for (int col = 0; col < TILEBLOCKSIZEX; col++) {
			auto tile = CTileMgr::GetInst()->GetTile(_row, _col, row, col);
			if (!tile) {
				auto under = CTileMgr::GetInst()->GetTile(_row, _col, row+1, col);
				if (under&& (under->GetTileType() == TileType::Soil || under->GetTileType() == TileType::Tree)) {
					int ran = GETRANDOM(100);
					if (ran < 95)
						continue;

					Ptr<CPrefab> prefab = CAssetMgr::GetInst()->Load<CPrefab>(SnakePrefKey, SnakePrefKey);
					auto obj = prefab->Instantiate();
					Vec3 pos = CTileMgr::GetInst()->IdxToPos(_row, _col, row, col);
					pos.z = MonsterZ;
					obj->Transform()->SetRelativePos(pos);
					GamePlayStatic::SpawnGameObject(obj, MonsterLayer);
				}
			}
		}
	}
}

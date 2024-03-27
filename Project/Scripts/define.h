#pragma once

#define TILEBLOCKSIZEX 10
#define TILEBLOCKSIZEY 8

#define STAGETILEROW 6
#define STAGETILECOL 6

#define TileScaleX 128
#define TileScaleY 128

#define TileBlockScaleX TileScaleX * TILEBLOCKSIZEX
#define TileBlockScaleY TileScaleY * TILEBLOCKSIZEY

#define TileBlockScaleVec Vec3(TileBlockScaleX, TileBlockScaleY, 1)

#define TileLayer 3

#define RandomAccuracy 100

#define GETRANDOM(bound) CRandomMgr::GetInst()->GetRandom(bound)

#define TilePrefKey L"prefab\\Tile.pref"

#define ChunkPath L"stage\\DwellingChunk.ck";

enum class StagePackList {
    Dwelling,
    END,
};

// Ÿ�� - �����, ��, ��(50%), ����, �ν����� ����, ��ٸ�, ��ٸ� �ݺ�, �ݺ�, �����̴� ��, ����, �����, ���ߵ��, �����
enum class BlockTileType
{
	Blank,
	Soil,
	Soil_50,
	Tree,
	NeverCrash,
	Ladder,
	LadderHalf,
	Half,
	Movable,
	Spike,
	ChunkGround,
	ChunkAir,
	ChunkDoor,
	END,
};

extern string StagePackListString[(int)StagePackList::END];


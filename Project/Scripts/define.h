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

// 타입 - 빈공간, 흙, 흙(50%), 나무, 부숴지지 않음, 사다리, 사다리 반벽, 반벽, 움직이는 돌, 가시, 땅덩어리, 공중덩어리, 문덩어리
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


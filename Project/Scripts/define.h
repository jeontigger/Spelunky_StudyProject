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

enum class StagePackList {
    Dwelling,
    END,
};

extern string StagePackListString[(int)StagePackList::END];
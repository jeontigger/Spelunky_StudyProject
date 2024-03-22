#pragma once

#define TILEBLOCKSIZEX 10
#define TILEBLOCKSIZEY 8

#define STAGETILEROW 4
#define STAGETILECOL 4

#define TileScaleX 128
#define TileScaleY 128

#define TileBlockScaleX TileScaleX * TILEBLOCKSIZEX
#define TileBlockScaleY TileScaleY * TILEBLOCKSIZEY

#define TileBlockScaleVec Vec3(TileBlockScaleX, TileBlockScaleY, 1)


enum class StagePackList {
    Dwelling,
    END,
};

extern string StagePackListString[(int)StagePackList::END];
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

#define DefaultGravity 20.5

#define CameraViewAll Vec2(5200, 4500)
#define CameraViewNormal Vec2(TileBlockScaleX * 1.3, TileBlockScaleY + TileScaleY)


#define BackgroundLayer 1
#define TileLayer 2
#define PlayerLayer 3
#define CameraLayer 6
#define MonsterLayer 7
#define DetectColliderLayer 8
#define PlayerHitLayer 9
#define MonsterHitLayer 10
#define ItemLayer 11
#define TileEmergencyLayer 30

#define RandomAccuracy 100
#define GETRANDOM(bound) CRandomMgr::GetInst()->GetRandom(bound)

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

enum class BoundaryTile {
	TOP,
	RIGHT,
	BUTTOM,
	LEFT,
	END,
};
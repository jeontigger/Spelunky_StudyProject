#pragma once
// (입구, 입구 낙하, 출구, 출구(낙하받이), 사이드, 좌우 경로, 낙하 경로, 낙하받이 경로, 낙하& 낙하받이 경로)
enum class TileBlockType{
	NONE,
	Entrance,
	Entrance_Fall,
	Exit,
	Exit_Drop,
	Normal,
	Fall,
	Drop,
	Fall_Drop,
	Side,
	END
};

// 타입 - 빈공간, 흙, 흙(50%), 나무, 반벽, 사다리, 가시
enum class BlockTileType
{
	Blank,
	Soil,
	Soil_50,
	Tree,
	Half,
	Ladder,
	Spike,
	END,
};

class CTileBlock
{
private:
	TileBlockType m_Type;
	BlockTileType m_Tiles[TILEBLOCKSIZE][TILEBLOCKSIZE];

public:

	CTileBlock();
	~CTileBlock();
};


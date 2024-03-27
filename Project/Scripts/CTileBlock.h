#pragma once

extern vector<string> TileBlockTypeStrings;
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

class CTileBlock
{
private:
	TileBlockType m_Type;
	BlockTileType m_Tiles[TILEBLOCKSIZEY][TILEBLOCKSIZEX];

public:
	/// <summary>
	/// row, col에 해당하는 타일의 타입을 설정합니다.
	/// </summary>
	inline void SetTileType(BlockTileType _type, int _row, int _col) { m_Tiles[_row][_col] = _type; }
	/// <summary>
	/// row, col에 해당하는 타일의 타입을 가져옵니다.
	/// </summary>
	inline BlockTileType GetTileType(int _row, int _col) const { return m_Tiles[_row][_col]; }

	/// <summary>
	/// 현재 타일 블록의 타입을 설정합니다.
	/// </summary>
	inline void SetBlockType(TileBlockType _type) { m_Type = _type; }
	/// <summary>
	/// 현재 타일 블록의 타입을 가져옵니다.
	/// </summary>
	inline TileBlockType GetBlockType() { return m_Type; }

	void TileInstancing(int row, int col);

public:
	friend ifstream& operator>>(ifstream& fin, CTileBlock& tileblock);
	friend ofstream& operator<<(ofstream& fout, const CTileBlock& tileblock);

public:
	CTileBlock();
	~CTileBlock();
};


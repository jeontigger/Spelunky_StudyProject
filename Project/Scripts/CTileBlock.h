#pragma once
// (�Ա�, �Ա� ����, �ⱸ, �ⱸ(���Ϲ���), ���̵�, �¿� ���, ���� ���, ���Ϲ��� ���, ����& ���Ϲ��� ���)
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

// Ÿ�� - �����, ��, ��(50%), ����, �ݺ�, ��ٸ�, ����
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
	inline void SetTileType(BlockTileType _type, int _row, int _col) { m_Tiles[_row][_col] = _type; }
	inline BlockTileType GetTileType(int _row, int _col) const { return m_Tiles[_row][_col]; }

public:
	void Save(ofstream& fout);
	void Load(ifstream& fin);

public:
	CTileBlock();
	~CTileBlock();
};


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

	CTileBlock();
	~CTileBlock();
};


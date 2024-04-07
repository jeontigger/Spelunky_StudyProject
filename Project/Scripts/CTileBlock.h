#pragma once

extern vector<string> TileBlockTypeStrings;
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
	NeverCrash,
	END
};

class CTileBlock
{
private:
	TileBlockType m_Type;
	BlockTileType m_Tiles[TILEBLOCKSIZEY][TILEBLOCKSIZEX];

public:
	/// <summary>
	/// row, col�� �ش��ϴ� Ÿ���� Ÿ���� �����մϴ�.
	/// </summary>
	inline void SetTileType(BlockTileType _type, int _row, int _col) { m_Tiles[_row][_col] = _type; }
	/// <summary>
	/// row, col�� �ش��ϴ� Ÿ���� Ÿ���� �����ɴϴ�.
	/// </summary>
	inline BlockTileType GetTileType(int _row, int _col) const { return m_Tiles[_row][_col]; }

	/// <summary>
	/// ���� Ÿ�� ����� Ÿ���� �����մϴ�.
	/// </summary>
	inline void SetBlockType(TileBlockType _type) { m_Type = _type; }
	/// <summary>
	/// ���� Ÿ�� ����� Ÿ���� �����ɴϴ�.
	/// </summary>
	inline TileBlockType GetBlockType() { return m_Type; }

	void TileInstancing(int row, int col);
	void MonsterGenerating(int row, int col);
	void ItemGenerating(int row, int col);

public:
	friend ifstream& operator>>(ifstream& fin, CTileBlock& tileblock);
	friend ofstream& operator<<(ofstream& fout, const CTileBlock& tileblock);

public:
	CTileBlock();
	~CTileBlock();
};


#pragma once

enum class ChunkType {
	Air,
	Ground,
	END,
};

class CTileChunk
{
private:
	int m_row;
	int m_col;
	ChunkType m_Type;
	vector<vector<BlockTileType>> m_Tiles;

public:
	void Init(int row, int col);
	void SetTileType(BlockTileType type, int row, int col);
	void SetType(ChunkType type) { m_Type = type; }

	void Instancing(int row, int col);

public:
	CTileChunk();
	~CTileChunk();

public:
	friend ofstream& operator<<(ofstream& fout, CTileChunk& chunk);
	friend ifstream& operator>>(ifstream& fin, CTileChunk& chunk);
};


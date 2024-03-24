#pragma once
#include "CFieldObject.h"

enum class SurroundTile {
    TOP,
    RIGHT,
    BUTTOM,
    LEFT,
    END,
};

enum class TileType {
    Blank,
	Soil,
	Tree,
	NeverCrash,
	Ladder,
	LadderHalf,
	Movable,
	Spike,
    Door,
    END,
}; 

class CTile :
    public CFieldObject
{
private:
    TileType m_type;
    TileType m_arrSurroundTiles[(int)SurroundTile::END];

public:
    void SetTileType(TileType type) { m_type = type; }
    TileType GetTileType() { return m_type; }

    void SetSurroundTileType(SurroundTile _dir, TileType _type) { m_arrSurroundTiles[(int)_dir] = _type; }
    TileType GetSurroundTileType(SurroundTile _dir) { return m_arrSurroundTiles[(int)_dir]; }

public:
    virtual void tick() override;

    virtual void skill() {};

    virtual void SaveToFile(FILE* _File) {};
    virtual void LoadFromFile(FILE* _File) {};

    CScript* Clone() { return this; };
public:
    CTile();
    ~CTile();
};

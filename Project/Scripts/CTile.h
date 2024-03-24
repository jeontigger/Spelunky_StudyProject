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
    virtual void tick() override;

    virtual void skill() {};

    virtual void SaveToFile(FILE* _File) {};
    virtual void LoadFromFile(FILE* _File) {};

    CScript* Clone() { return this; };
public:
    CTile(TileType type);
    ~CTile();
};


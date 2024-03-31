#pragma once
#include "CFieldObject.h"


enum class TileType {
    Blank,
	Soil,
	Tree,
	NeverCrash,
	Ladder,
	LadderHalf,
    Half,
	Movable,
	Spike,
    Door,
    END,
}; 

class CTile :
    public CFieldObject
{
private:
    static int TileCount;
    TileType m_type;
    TileType m_arrSurroundTiles[(int)BoundaryTile::END];

public:
    void Instancing(TileType type, int row, int col);
    void SetTileType(TileType type);
    TileType GetTileType() { return m_type; }

    void SetSurroundTileType(BoundaryTile _dir, TileType _type) { m_arrSurroundTiles[(int)_dir] = _type; }
    TileType GetSurroundTileType(BoundaryTile _dir) { return m_arrSurroundTiles[(int)_dir]; }

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)override {} ;
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override {};

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void skill() {};

    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};

    CLONE(CTile);
public:
    CTile();
    CTile(const CTile& tile);
    ~CTile();

private:
    Vec2 TypeToPos(TileType type);
};


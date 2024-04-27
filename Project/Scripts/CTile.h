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
    ExitDoor,
    END,
}; 

class CTile :
    public CFieldObject
{
private:
    float   m_PermitRange;

private:
    static int TileCount;
    TileType m_type;
    CGameObject* m_arrSurroundTiles[(UINT)TileDir::END];

public:
    void Instancing(TileType type, int row, int col);
    void SetTileType(TileType type);
    TileType GetTileType() { return m_type; }

public:
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)override ;
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) override;

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

private:
    void UpCollision(CGameObject* _Obj, float _PlatformTop, float _ObjColScaleY);
    void DownCollision(CGameObject* _Obj, float _PlatformBottom, float _ObjColScaleY);
    void LeftCollision(CGameObject* _Obj, float _PlatformLeft, float _ObjColScaleX);
    void RightCollision(CGameObject* _Obj, float _PlatformRight, float _ObjColScaleX);
};


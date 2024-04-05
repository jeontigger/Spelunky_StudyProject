#pragma once
#include <Engine/singleton.h>

union TileCollisionID
{
    struct
    {
        UINT LeftID;
        UINT RightID;
    };

    UINT_PTR id;
};

class CTile;
class CTileMgr :
    public CSingleton<CTileMgr>
{
private:
    UINT m_LayerCheck;
    map<UINT_PTR, bool>		m_mapPrevInfo;

public:
    void CheckLayer(UINT _layer);

private:
    class CGameObject* m_arrTiles[STAGETILEROW][STAGETILECOL][TILEBLOCKSIZEY][TILEBLOCKSIZEX];

public:
    void SetTile(CGameObject* tile, int _blockRow, int _blockCol, int _tileRow, int _tileCol);
    CTile* GetTile(Vec2 _idx);
    CTile* GetTile(int _blockRow, int _blockCol, int _tileRow, int _tileCol);
    CCollider2D* GetTileCollider(Vec2 _idx);
    
    Vec2 PosToIdx(Vec3 _vPos);
    Vec3 IdxToPos(Vec2 _Idx);
    Vec3 IdxToPos(int _BlockRow, int _BlockCol, int _TileRow, int _TileCol);

public:
    void tick();
    void CollisionWithTile(int _layer);
    bool CheckCollision(CCollider2D* _left, CCollider2D* _right);

public:
    CTileMgr();
    ~CTileMgr();
};


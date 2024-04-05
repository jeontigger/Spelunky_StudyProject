#pragma once
#include <Engine/singleton.h>

class CTile;
class CTileMgr :
    public CSingleton<CTileMgr>
{
private:
    class CGameObject* m_arrTiles[STAGETILEROW][STAGETILECOL][TILEBLOCKSIZEY][TILEBLOCKSIZEX];

public:
    void SetTile(CGameObject* tile, int _blockRow, int _blockCol, int _tileRow, int _tileCol);
    CTile* GetTile(Vec2 _idx);
    CTile* GetTile(int _blockRow, int _blockCol, int _tileRow, int _tileCol);
    
    Vec2 PosToIdx(Vec3 _vPos);
    Vec3 IdxToPos(Vec2 _Idx);
    Vec3 IdxToPos(int _BlockRow, int _BlockCol, int _TileRow, int _TileCol);

public:
    CTileMgr();
    ~CTileMgr();
};


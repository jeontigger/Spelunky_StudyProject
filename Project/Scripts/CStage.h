#pragma once
#include <Engine/CLevel.h>

class CTileBlock;
class CStage :
    public CLevel
{
private:
    vector<vector<CTileBlock>> m_TileBlocks;
    Ptr<CTexture> m_texBackground;


public:
    CStage();
    ~CStage();
};


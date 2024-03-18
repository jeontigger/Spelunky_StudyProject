#pragma once
#include <Engine/CLevel.h>

class CTileBlock;
class CStage :
    public CLevel
{
private:
    vector<vector<CTileBlock>> m_TileBlocks;


public:
    CStage();
    ~CStage();
};


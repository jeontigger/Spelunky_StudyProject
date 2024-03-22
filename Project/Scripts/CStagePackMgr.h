#pragma once
#include <Engine/singleton.h>

#include "CStagePack.h"

class CStagePackMgr :
    public CSingleton<CStagePackMgr>
{
private:
    class CStagePack* m_arrPacks[(int)StagePackList::END];

public:
    inline CStagePack* GetStagePack(StagePackList _num) { return m_arrPacks[(int)_num]; }

public:
    CStagePackMgr();
    ~CStagePackMgr();
};


#pragma once
#include <Engine/CLevel.h>

class CStage :
    public CLevel
{
private:
    class CStagePack* m_SP;


public:
    void SetStagePack(StagePackList _num);

public:
    CStage();
    ~CStage();
};


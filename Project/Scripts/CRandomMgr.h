#pragma once
#include <Engine/singleton.h>

#include <random>

class CRandomMgr :
    public CSingleton<CRandomMgr>
{
private:
    UINT32 m_seed;
    std::mt19937 m_GenEngine;
    std::uniform_int_distribution<> m_DistGenerator;

    wstring m_strPrint;

public:
    void init();

    int GetRandom(int _bound);
    bool RandomSucceed(int _probability, int _bound);

    void GenNewSeed(UINT32 _seed);

    UINT32 GetSeed() { return m_seed; }
    void SetSeed(UINT32 _seed);

public:
    CRandomMgr();
    ~CRandomMgr();
};


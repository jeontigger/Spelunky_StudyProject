#pragma once
#include "singleton.h"
class CChronoMgr :
    public CSingleton<CChronoMgr>
{
private:
	std::chrono::steady_clock::time_point m_start;

public:
	void Start();
	std::chrono::milliseconds End();

public:
	CChronoMgr();
	~CChronoMgr();
};


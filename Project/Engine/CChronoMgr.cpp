#include "pch.h"
#include "CChronoMgr.h"

CChronoMgr::CChronoMgr()
{
}

CChronoMgr::~CChronoMgr()
{
}

void CChronoMgr::Start()
{
	m_start = std::chrono::high_resolution_clock::now();
}

std::chrono::milliseconds CChronoMgr::End()
{
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start);

	return duration;
}
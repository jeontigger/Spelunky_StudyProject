#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLayer.h>
#include <Engine/CLevelMgr.h>

#include	<Scripts/CStage.h>
#include <Scripts/CStagePack.h>
#include <Scripts/CStagePackMgr.h>
#include <Scripts/CRandomMgr.h>

CLevel* CLevelGenerator::m_pTempLevel = nullptr;
CStage* CLevelGenerator::m_arrStages[4] = {};

CLevelGenerator::CLevelGenerator()
{
}

CLevelGenerator::~CLevelGenerator()
{
	if (m_pTempLevel)
		delete m_pTempLevel;
}

void CLevelGenerator::Init()
{
	CStage* stage = new CStage;

	CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
	stage->SetStagePack(sp);

	m_arrStages[0] = stage;

	CRandomMgr::GetInst()->init();

	UINT32 seed = CRandomMgr::GetInst()->GetSeed();

	string logpath = ToString(CPathMgr::GetContentPath()) + GameLogPath;
	ofstream fout(logpath);
	if (fout.is_open()) {
		fout << "seed: " << seed << endl;
	}

	m_pTempLevel = new CLevel;
	LoadTempLevel();
}

CStage* CLevelGenerator::LoadLevels(int _level)
{
	return m_arrStages[_level];
}

void CLevelGenerator::LoadTempLevel()
{
	CLevelMgr::GetInst()->ChangeLevel(m_pTempLevel, LEVEL_STATE::STOP);
}

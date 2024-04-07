#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLayer.h>
#include <Engine/CLevelMgr.h>

#include	<Scripts/CStage.h>
#include <Scripts/CStagePack.h>
#include <Scripts/CStagePackMgr.h>
#include <Scripts/CRandomMgr.h>

CLevel* CLevelGenerator::m_pTempLevel = nullptr;
CStage* CLevelGenerator::m_arrStages[StageCnt] = {};

void CLevelGenerator::Init()
{
	m_pTempLevel = new CLevel;

	DestroyStages();
}

void CLevelGenerator::MakeStages()
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
}

CStage* CLevelGenerator::GetLevel(int _level)
{
	return m_arrStages[_level];
}

void CLevelGenerator::DestroyStages()
{
	for (int i = 0; i < StageCnt; i++) {
		if (m_arrStages[i])
			delete m_arrStages[i];
	}

	CLevelMgr::GetInst()->ChangeLevel_Task(m_pTempLevel, LEVEL_STATE::STOP);
}

void CLevelGenerator::Destroy()
{
	if (m_pTempLevel)
		delete m_pTempLevel;

	for (int i = 0; i < StageCnt; i++) {
		if (m_arrStages[i])
			delete m_arrStages[i];
	}
}

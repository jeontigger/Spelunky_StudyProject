#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLayer.h>
#include <Engine/CLevelMgr.h>

#include	<Scripts/CStage.h>
#include <Scripts/CStagePack.h>
#include <Scripts/CStagePackMgr.h>
#include <Scripts/CRandomMgr.h>

void CLevelGenerator::LoadLevels()
{
	CStage* stage = new CStage;

	CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
	stage->SetStagePack(sp);

	CRandomMgr::GetInst()->init();

	UINT32 seed = CRandomMgr::GetInst()->GetSeed();

	string logpath = ToString(CPathMgr::GetContentPath()) + GameLogPath;
	ofstream fout(logpath);
	if (fout.is_open()) {
		fout << "seed: " << seed << endl;
	}
}

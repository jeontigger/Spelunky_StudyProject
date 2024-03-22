#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLayer.h>
#include <Engine/CLevelMgr.h>

#include	<Scripts/CStage.h>
#include <Scripts/CStagePack.h>
#include <Scripts/CStagePackMgr.h>

void CLevelGenerator::LoadLevels()
{
	CStage* stage = new CStage;

	CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
	stage->SetStagePack(sp);
}

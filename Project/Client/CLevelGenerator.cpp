#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLevelMgr.h>


#include <Scripts/CStage.h>


void CLevelGenerator::LoadLevels()
{

	vector<string> m_vecStagePaths;
	Utils::LoadAllPath("stage", m_vecStagePaths);

	//m_vecStagePaths;

	CStagePack* stage = new CStagePack;
	for (int i = 0; i < m_vecStagePaths.size(); i++) {
		//stage->Load(m_vecStagePaths[i]);
	}
}

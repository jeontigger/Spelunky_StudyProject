#include "pch.h"
#include "CLevelGenerator.h"

#include <Engine/CLayer.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CDevice.h>

#include <Scripts/CTitleLevel.h>
#include	<Scripts/CStage.h>
#include <Scripts/CStagePack.h>
#include <Scripts/CStagePackMgr.h>
#include <Scripts/CRandomMgr.h>

CLevel* CLevelGenerator::m_pTempLevel = nullptr;
CLevel* CLevelGenerator::m_arrStages[StageCnt] = {};

UINT32 CLevelGenerator::GetSeed()
{
	string logpath = ToString(CPathMgr::GetContentPath()) + GameLogPath;
	ifstream fin(logpath);
	string str;
	istringstream iss;
	while (true) {
		if (!getline(fin, str))
			break;
		if (str.find("seed")) {
			iss.str(str);
			string temp;
			UINT32 seed;
			iss >> temp >> seed;
			return seed;
		}
	}
	return 0;
}

void CLevelGenerator::Init()
{
	m_pTempLevel = new CLevel;
	// Player Object »ý¼º
	CGameObject* pObj = new CGameObject;
	pObj->SetName(StrPlayerName);

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);

	pObj->Transform()->SetRelativePos(Vec3(-9000.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	m_pTempLevel->AddObject(pObj, PlayerLayer);

	DestroyStages();
	LoadTempLevel();
}

void CLevelGenerator::TitleLevel()
{
	CTitleLevel* title = new CTitleLevel;
	m_arrStages[0] = title;

}

#include <Scripts/CUI.h>
void CLevelGenerator::MakeStages()
{
	TitleLevel();
	/*CStage* stage = new CStage;

	CStagePack* sp = CStagePackMgr::GetInst()->GetStagePack(StagePackList::Dwelling);
	stage->SetStagePack(sp);

	m_arrStages[0] = stage;

	UINT32 seed = CRandomMgr::GetInst()->GetSeed();

	string logpath = ToString(CPathMgr::GetContentPath()) + GameLogPath;
	ofstream fout(logpath);
	if (fout.is_open()) {
		fout << "seed: " << seed << endl;
	}

	Ptr<CPrefab> prefab;
	CGameObject* obj;

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDHeartPrefKey, HUDHeartPrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(80, 80));
	obj->Animator2D()->Play(AnimHUDHeart);

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDBombPrefKey, HUDBombPrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(200, 80));
	obj->Animator2D()->Play(AnimHUDBomb);

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDRopePrefKey, HUDRopePrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2(320, 80));
	obj->Animator2D()->Play(AnimHUDRope);

	Vec2 resolution = CDevice::GetInst()->GetRenderResolution();
	resolution *= stage->GetUICamera()->Camera()->GetScale();

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDScorePrefKey, HUDScorePrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2((int)resolution.x - 480, 80));
	obj->Animator2D()->Play(AnimHUDScore);

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDTimePrefKey, HUDTimePrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2((int)resolution.x - 300, 80));
	obj->Animator2D()->Play(AnimHUDTime);

	prefab = CAssetMgr::GetInst()->Load<CPrefab>(HUDStagePrefKey, HUDStagePrefKey);
	obj = prefab->Instantiate();
	stage->AddObject(obj, UILayer);
	obj->GetScript<CUI>()->SetScreenPos(Vec2((int)resolution.x - 120, 80));
	obj->Animator2D()->Play(AnimHUDStage);*/
		
}

CLevel* CLevelGenerator::GetLevel(int _level)
{
	return m_arrStages[_level];
}

void CLevelGenerator::LoadTempLevel()
{
	CLevelMgr::GetInst()->ChangeLevel_Task(m_pTempLevel, LEVEL_STATE::STOP);
}

void CLevelGenerator::DestroyStages()
{
	for (int i = 0; i < StageCnt; i++) {
		if (m_arrStages[i])
			delete m_arrStages[i];
	}
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

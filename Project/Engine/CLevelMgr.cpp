#include "pch.h"
#include "CLevelMgr.h"

#include "CRenderMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CDevice.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"

#include "CTaskMgr.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	//if (nullptr != m_CurLevel)
	//	delete m_CurLevel;
	if (nullptr != m_StartLevel) {
		delete m_StartLevel;
	}
}

void CLevelMgr::ChangeToStartLevel(float _delay)
{
	ChangeLevel(m_StartLevel, LEVEL_STATE::PLAY, _delay);
}

void CLevelMgr::init()
{

}
#include "CChronoMgr.h"
void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	// 이전 프레임에 등록된 오브젝트들 clear
	m_CurLevel->clear();
	// 레벨이 Play 상태일 경우에만 tick() 호출
	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->tick();
	}
	CChronoMgr::GetInst()->Start();
	m_CurLevel->finaltick();
	auto time = CChronoMgr::GetInst()->End();
	CChronoMgr::GetInst()->Start();

	// 충돌 처리
	CCollisionMgr::GetInst()->tick();
	time = CChronoMgr::GetInst()->End();
	CChronoMgr::GetInst()->Start();
	// Render
	CRenderMgr::GetInst()->tick();
	time = CChronoMgr::GetInst()->End();
	CChronoMgr::GetInst()->Start();
	
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextLevelStartState, float _Delay)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVEL;
	task.Param_1 = (DWORD_PTR)_NextLevel;	
	task.Param_2 = (DWORD_PTR)_NextLevelStartState;
	task.Param_3 = _Delay;

	CTaskMgr::GetInst()->AddTask(task);	
}

void CLevelMgr::ChangeLevelState(LEVEL_STATE _State, float _Delay)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVELSTATE;
	task.Param_1 = (DWORD_PTR)m_CurLevel;
	task.Param_2 = (DWORD_PTR)_State;
	task.Param_3 = _Delay;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState)
{
	assert(!(m_CurLevel == _NextLevel));
		
	/*if (nullptr != m_CurLevel)
		delete m_CurLevel;*/

	m_CurLevel = _NextLevel;

	if (nullptr != m_CurLevel)
		m_CurLevel->ChangeState(_NextLevelState);
}

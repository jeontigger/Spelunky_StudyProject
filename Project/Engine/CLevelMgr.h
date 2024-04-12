#pragma once
#include "singleton.h"

class CLevel;

class CLevelMgr :
    public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr);
private:
    CLevel*         m_CurLevel;
    CLevel* m_StartLevel;

public:
    void SetStartLevel(CLevel* _level) { m_StartLevel = _level; }
    void ChangeToStartLevel(float _delay);

public:
    void init();        
    void tick();  

public:
    void ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextStartState, float _Delay = 0.f);
    void ChangeLevelState(LEVEL_STATE _State, float _Delay = 0.f);

public:
    void ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState);


public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }
    friend class CTaskMgr;
};


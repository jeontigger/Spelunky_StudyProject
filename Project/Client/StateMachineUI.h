#pragma once
#include "ComponentUI.h"
class StateMachineUI :
    public ComponentUI
{
private:
    CStateMachine* m_StateMachine;
    Ptr<CFSM> m_FSM;
    map<wstring, class CState*> m_States;
    vector<string> m_vecNames;

public:
    void FSMSelect(DWORD_PTR _ptr);

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    StateMachineUI();
    ~StateMachineUI();

private:
    // FSM 선택지
    void SelectFSM();
    // 현재 스테이트 출력
    void CurState();
    // 스테이트 목록 출력 + change state
    void StateList();
};


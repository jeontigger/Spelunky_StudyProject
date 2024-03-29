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
    // FSM ������
    void SelectFSM();
    // ���� ������Ʈ ���
    void CurState();
    // ������Ʈ ��� ��� + change state
    void StateList();
};


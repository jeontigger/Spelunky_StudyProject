#pragma once
#include "CAsset.h"

#include "CState.h"
#include "CBlackboard.h"

class CStateMachine;

class CFSM :
    public CAsset
{
private:
    CFSM*                   m_Master;
    CStateMachine*          m_StateMachine; // FSM 을 사용하는 StateMachine;

    map<wstring, CState*>   m_mapState;
    CBlackboard*            m_Blackboard;

    CState*                 m_CurState;



public:
    void AddState(const wstring& _StateName, CState* _State);
    CState* FindState(const wstring& _StateName);
    void SetState(const wstring& _strState);
    void SetStateMachine(CStateMachine* _SM)
    { 
        if (m_Master) 
        { 
            m_StateMachine = _SM; 
        } 
    }
    CFSM* GetFSMIstance();

    CStateMachine* GetStateMachine() { return m_StateMachine; }
    void ChangeState(const wstring& _strStateName);
    CState* GetCurState() { return m_CurState; }

    template<typename T>
    T* GetState()
    {
        for (auto iter = m_mapState.begin(); iter != m_mapState.end(); ++iter)
        {
            if (dynamic_cast<T*>(iter->second))
                return (T*)iter->second;
        }
        return nullptr;
    }


public:
    void finaltick();

public:
    virtual int Save(const wstring& _strRelativePath);
    virtual int Load(const wstring& _strFilePath);

    static CState* (*LoadStateFunc)(const string& _strFilePath);

public:
    CLONE(CFSM);
    CFSM(bool _bEngine = false);
    ~CFSM();   

private:
    map<wstring, CState*>& GetStates() { return m_mapState; }
    friend class FSMUI;
    friend class StateMachineUI;
    friend class CStateMachine;
};


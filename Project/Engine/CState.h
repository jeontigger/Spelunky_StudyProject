#pragma once
#include "CEntity.h"


class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:
    UINT m_iStateType;
    CFSM*       m_FSM;

public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

protected:
    void* GetBlackboardData(const wstring& _strKey);
    CFSM* GetFSM() { return m_FSM; }

    void ChangeState(const wstring& _strStateName);

public:
    UINT GetStateType() { return m_iStateType; }

public:
    CLONE_DISABLE(CState);

    CState();
    ~CState();

    friend class CFSM;

public:
    virtual void Save(ofstream& fout);
    virtual void Load(ifstream& fin);
};

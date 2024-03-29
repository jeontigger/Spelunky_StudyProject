#include "pch.h"
#include "CFSM.h"

CState* (*CFSM::LoadStateFunc)(const string& _strFilePath) = nullptr;

CFSM::CFSM(bool _bEngine)
	: CAsset(ASSET_TYPE::FSM, _bEngine)
	, m_Master(nullptr)
	, m_Blackboard(nullptr)	
{
}

CFSM::~CFSM()
{
	if (m_Blackboard)
		delete m_Blackboard;

	if (!m_Master)
	{
		Delete_Map(m_mapState);
	}
}

void CFSM::finaltick()
{
	if (m_CurState)
	{
		m_CurState->m_FSM = this;
		m_CurState->finaltick();
	}
}

int CFSM::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	ofstream fout(strFilePath);

	if (!fout.is_open())
		return E_FAIL;

	fout << GetName() << endl;

	fout << m_mapState.size() << endl;

	for (auto iter = m_mapState.begin(); iter != m_mapState.end(); ++iter) {
		fout << iter->first << endl;
		iter->second->Save(fout);
	}

	return S_OK;
}

int CFSM::Load(const wstring& _strFilePath)
{
	ifstream fin(_strFilePath);

	if (!fin.is_open()) return E_FAIL;
	string name;
	fin >> name;

	int stateCnt;
	fin >> stateCnt;
	for (int i = 0; i < stateCnt; i++) {
		string statename;
		fin >> statename;

		CState* state = nullptr;
		if (LoadStateFunc)
			state = LoadStateFunc(statename);
		state->SetName(statename);
		AddState(ToWString(statename), state);
		state->Load(fin);
	}
	
	return MB_OK;
}

void CFSM::AddState(const wstring& _StateName, CState* _State)
{
	if (FindState(_StateName)) {
		MessageBox(nullptr, L"중복된 스테이트입니다", L"FSM", 0);
		return;
	}

	_State->m_FSM = this;
	m_mapState.insert(make_pair(_StateName, _State));
}

CState* CFSM::FindState(const wstring& _StateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_StateName);

	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;
}

void CFSM::SetState(const wstring& _strState)
{
	m_CurState = FindState(_strState);
}

CFSM* CFSM::GetFSMIstance()
{
	CFSM* pFSMInst = new CFSM;

	pFSMInst->m_mapState = m_mapState;
	pFSMInst->m_Master = this;
	pFSMInst->m_Blackboard = nullptr;
	pFSMInst->m_CurState = nullptr;

	return pFSMInst;
}

void CFSM::ChangeState(const wstring& _strStateName)
{
	if(nullptr != m_CurState)
		m_CurState->Exit();

	m_CurState = FindState(_strStateName);

	assert(m_CurState);

	m_CurState->Enter();
}

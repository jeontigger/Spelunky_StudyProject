#include "pch.h"
#include "StateMachineUI.h"

#include <Engine/CStateMachine.h>

StateMachineUI::StateMachineUI()
	: ComponentUI("StateMachine", UIStateMachineName, COMPONENT_TYPE::STATEMACHINE)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("StateMachine");

}

StateMachineUI::~StateMachineUI()
{
}

void StateMachineUI::render_update()
{
	ComponentUI::render_update();

	// FSM 선택지
	SelectFSM();
	// 현재 스테이트 출력
	if (m_FSM.Get())
		CurState();
	// 스테이트 목록 출력 + change state
	if(m_FSM.Get())
		StateList();
}

void StateMachineUI::Activate()
{
	ComponentUI::Activate();

	m_StateMachine = (CStateMachine*)GetTargetObject()->GetComponent(COMPONENT_TYPE::STATEMACHINE);
}

#include "ListUI.h"
void StateMachineUI::SelectFSM()
{
	string fsmname;
	m_FSM = m_StateMachine->GetOriginFSM();
	if (nullptr != m_FSM)
	{
		fsmname = ToString(m_FSM->GetRelativePath()).c_str();
	}
	ImGui::Text("FSM    ");
	ImGui::SameLine();
	ImGui::InputText("##FSMName", (char*)fsmname.c_str(), fsmname.length(), ImGuiInputTextFlags_ReadOnly);

	// Mesh Drop 체크
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::FSM == pAsset->GetType())
			{
				m_StateMachine->SetFSM((CFSM*)pAsset);
			}
		}
		ImGui::EndDragDropTarget();
	}

	ImGui::SameLine();
	if (ImGui::Button("##FSMBtn", ImVec2(20, 20)))
	{
		// 리스트 UI
		ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

		vector<string> vecFSMName;
		CAssetMgr::GetInst()->GetAssetName(ASSET_TYPE::FSM, vecFSMName);

		pListUI->AddString(vecFSMName);
		//pListUI->SetDbClickCallBack(MeshSelect);
		pListUI->SetDbClickDelegate(this, (Delegate_1)&StateMachineUI::FSMSelect);
		pListUI->Activate();
	}

}

void StateMachineUI::CurState()
{
	CState* state = m_StateMachine->GetFSM()->GetCurState();
	ImGui::Text("CurState");
	ImGui::SameLine();
	string name;
	if(state != nullptr)
		name = ToString(state->GetName());
	ImGui::InputText("##cursatteName", (char*)name.c_str(), name.length(), ImGuiInputTextFlags_ReadOnly);
}

void StateMachineUI::StateList()
{
	map<wstring, CState*>& states = m_FSM->GetStates();
	for (auto iter = states.begin(); iter != states.end();++iter) {
		string statename = ToString(iter->first);
		ImGui::InputText("##statename", (char*)statename.c_str(), statename.length(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();

		if (ImGui::Button("Change")) {
			m_StateMachine->SetFSM(m_FSM);
			m_StateMachine->GetFSM()->ChangeState(iter->first);
		}
	}
	SetSize(ImVec2(0, 80 + states.size() * 25));
}

void StateMachineUI::FSMSelect(DWORD_PTR _ptr)
{
	string strMesh = (char*)_ptr;
	wstring strMeshName = ToWString(strMesh);

	Ptr<CFSM> pFSM = CAssetMgr::GetInst()->FindAsset<CFSM>(strMeshName);

	m_StateMachine->SetFSM(pFSM);
}
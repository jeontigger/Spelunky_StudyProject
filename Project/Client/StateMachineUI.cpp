#include "pch.h"
#include "StateMachineUI.h"

#include <Engine/CStateMachine.h>
#include <Engine/CBlackboard.h>
#include <Engine/CGameObject.h>

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

	// 블랙 보드 출력
	if (m_FSM.Get())
		Blackboard();

	ImGui::Separator();

	// 현재 스테이트 출력
	if (m_FSM.Get())
		CurState();
	 // 스테이트 목록 출력 + change state
	if(m_FSM.Get())
		StateList();

	SetSize(ImVec2(0, 80 + m_iStateCnt * 25 + m_iBlackboardCnt * 25));

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

void StateMachineUI::Blackboard()
{
	auto boards = m_StateMachine->m_Blackboard.m_mapBBData;
	m_iBlackboardCnt = boards.size();
	int cnt = 0;
	for (auto iter = boards.begin(); iter != boards.end(); ++iter) {
		auto data = *iter;
		string str = ToString(data.first);
		ImGui::Text(str.c_str()); ImGui::SameLine();
		auto type = data.second.Type;
		auto pointer = data.second.pData;
		string key = "##BlackboardData" + std::to_string(cnt);
		switch (type)
		{
		case BB_DATA::INT:
			ImGui::InputInt(key.c_str(), (int*)pointer, 1, 100, ImGuiInputTextFlags_ReadOnly);
			break;
		case BB_DATA::FLOAT:
			ImGui::InputFloat(key.c_str(), (float*)pointer, 1, 100, "%.3f",  ImGuiInputTextFlags_ReadOnly);
			break;
		case BB_DATA::VEC2:
			ImGui::InputFloat2(key.c_str(), (float*)pointer, "%.3f", ImGuiInputTextFlags_ReadOnly);
			break;
		case BB_DATA::VEC3:
			ImGui::InputFloat3(key.c_str(), (float*)pointer, "%.3f", ImGuiInputTextFlags_ReadOnly);
			break;
		case BB_DATA::VEC4:
			ImGui::InputFloat4(key.c_str(), (float*)pointer, "%.3f", ImGuiInputTextFlags_ReadOnly);
			break;
		case BB_DATA::OBJECT:
		{
			CGameObject* obj = (CGameObject*)pointer;
			ImGui::InputText(key.c_str(), (char*)ToString(obj->GetName()).c_str(), ToString(obj->GetName()).length(), ImGuiInputTextFlags_ReadOnly);
		}
			break;
		default:
			break;
		}
	}


}

void StateMachineUI::CurState()
{
	if (!m_StateMachine->m_FSM_Inst.Get()) {
		return;
	}

	CState* state = m_StateMachine->m_FSM_Inst->m_CurState;
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
	m_iStateCnt = states.size();
	int cnt = 0;
	for (auto iter = states.begin(); iter != states.end();++iter) {
		string statename = ToString(iter->first);
		string textkey = "##statename" + to_string(cnt);
		string buttonkey = "Change##" + to_string(cnt);
		cnt++;
		ImGui::InputText(textkey.c_str(), (char*)statename.c_str(), statename.length(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();

		if (ImGui::Button(buttonkey.c_str())) {
			m_StateMachine->m_FSM_Inst->ChangeState(iter->first);
		}
	}
}

void StateMachineUI::FSMSelect(DWORD_PTR _ptr)
{
	string strMesh = (char*)_ptr;
	wstring strMeshName = ToWString(strMesh);

	Ptr<CFSM> pFSM = CAssetMgr::GetInst()->FindAsset<CFSM>(strMeshName);

	m_StateMachine->SetFSM(pFSM);
}
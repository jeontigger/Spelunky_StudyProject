#include "pch.h"
#include "Animator2DUI.h"

#include <Engine/CAnimator2D.h>

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("Animator2D");

	LoadAnims();
}

Animator2DUI::~Animator2DUI()
{
}

void Animator2DUI::render_update()
{
	ComponentUI::render_update();

	CurAnim();

	AnimList();

	ImGui::Separator();
	AddAnim();

	SetSize(ImVec2(0, 180 + 28 * m_iAnimCnt));
}

void Animator2DUI::Activate()
{
	ComponentUI::Activate();

	m_target = GetTargetObject()->Animator2D();
}

void Animator2DUI::CurAnim()
{
	ImGui::Text("CurrentAnim"); ImGui::SameLine();

	string animName;
	if (m_target->GetCurAnim())
		animName = ToString(m_target->GetCurAnim()->GetName());
	ImGui::InputText("##curanimname", (char*)animName.c_str(), animName.length(), ImGuiInputTextFlags_ReadOnly);
}

void Animator2DUI::AnimList()
{
	const map<wstring, CAnim*>& list = m_target->m_mapAnim;
	m_iAnimCnt = list.size();
	
	if (m_iAnimCnt > 0) {
		ImGui::Separator();
		ButtonTitle("AnimList");
		ImGui::NewLine();
	}
	else {
		return;
	}

	int cnt = 0;
	static bool repeat = false;
	if(ImGui::Checkbox("IsRepeat", &repeat));

	for (auto iter = list.begin(); iter != list.end();) {
		string key = "##animname" + to_string(cnt);
		string buttonKey = "Play##anim" + to_string(cnt);
		string DeleteKey = "Delete##anim" + to_string(cnt);

		string animname = ToString(iter->first);

		ImGui::InputText(key.c_str(), (char*)animname.c_str(), animname.length(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		if (ImGui::Button(buttonKey.c_str())) {
			m_target->Play(ToWString(animname), repeat);
		}
		ImGui::SameLine();
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
		if (ImGui::Button(DeleteKey.c_str())) {
			delete iter->second;
			iter = m_target->m_mapAnim.erase(iter);
			m_target->m_CurAnim = nullptr;
		}
		else {
			++iter;
		}
		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}
}

void Animator2DUI::AddAnim()
{
	ButtonTitle("AddAnim");

	static int current_item = 0;
	if (ImGui::Button("Add##addanim")) {
		CAnim* anim = new CAnim;

		string path = ToString(CPathMgr::GetContentPath()) + m_vecAnimNames[current_item];

		ifstream fin(path);
		if (!fin.is_open()) {
			MessageBox(nullptr, L"경로 오류!", L"애니메이션 추가", 0);
			return;
		}
		anim->LoadFromFile(fin);
		anim->SetName(m_vecAnimNames[current_item]);
		m_target->AddAnim(anim);

	}
	SearchableComboBox("addstateuicombo", &current_item, m_vecAnimNames);
}

void Animator2DUI::LoadAnims()
{
	Utils::LoadAllPath("anim", m_vecAnimNames);
}

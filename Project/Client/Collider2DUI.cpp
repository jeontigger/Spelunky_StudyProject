#include "pch.h"
#include "Collider2DUI.h"

#include	<Engine/CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
	, m_collider(nullptr)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComponentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Activate()
{
	ComponentUI::Activate();

	m_collider = (CCollider2D*)GetTargetObject()->GetComponent(COMPONENT_TYPE::COLLIDER2D);
}

void Collider2DUI::render_update()
{
	ComponentUI::render_update();

	Vec2 pos = m_collider->GetOffsetPos();
	Vec2 scale = m_collider->GetOffsetScale();
	bool absolute = m_collider->IsAbsolute();

	ImVec2 impos(pos.x, pos.y);
	
	ImGui::Text("Offset Pos"); ImGui::SameLine(); ImGui::DragFloat2("##collideroffsetpos", (float*)&pos);
	ImGui::Text("Offset scale"); ImGui::SameLine(); ImGui::DragFloat2("##collideroffsetscale", (float*)&scale);
	ImGui::Checkbox("IsAbsolute", &absolute);

	m_collider->SetOffsetPos(pos);
	m_collider->SetOffsetScale(scale);
	m_collider->SetAbsolute(absolute);
}
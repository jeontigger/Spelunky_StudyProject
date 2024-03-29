#include "pch.h"
#include "StateMachineUI.h"

StateMachineUI::StateMachineUI()
	: ComponentUI("StateMachine", UIStateMachineName, COMPONENT_TYPE::STATEMACHINE)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComopnentTitle("StateMachine");
}

StateMachineUI::~StateMachineUI()
{
}

void StateMachineUI::render_update()
{
	ComponentUI::render_update();
}

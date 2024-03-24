#include "pch.h"
#include "GraphicsShaderUI.h"

#include <Engine/CGraphicsShader.h>

GraphicsShader::GraphicsShader()
	: AssetUI("GraphicsShader", "##GraphicsShader", ASSET_TYPE::GRAPHICS_SHADER)
{
}

GraphicsShader::~GraphicsShader()
{
}


void GraphicsShader::render_update()
{
	AssetUI::render_update();

	string path, func;

	m_shader->GetVSInfo(path, func);
	if (path != "" && func != "") {
		ButtonTitle("Vertex Shader"); ImGui::NewLine();
		DisplayInfo(path, func);
	}

	m_shader->GetHSInfo(path, func);
	if (path != "" && func != "") {
		ButtonTitle("Hull Shader"); ImGui::NewLine();
		DisplayInfo(path, func);
	}

	m_shader->GetDSInfo(path, func);
	if (path != "" && func != "") {
		ButtonTitle("Domain Shader"); ImGui::NewLine();
		DisplayInfo(path, func);
	}

	m_shader->GetGSInfo(path, func);
	if (path != "" && func != "") {
		ButtonTitle("Geometry Shader"); ImGui::NewLine();
		DisplayInfo(path, func);
	}

	m_shader->GetPSInfo(path, func);
	if (path != "" && func != "") {
		ButtonTitle("Pixel Shader"); ImGui::NewLine();
		DisplayInfo(path, func);
	}
}

void GraphicsShader::Activate()
{
	AssetUI::Activate();

	m_shader = (CGraphicsShader*)GetAsset().Get();
}

void GraphicsShader::DisplayInfo(const string& path, const string& func)
{
	ImGui::Text("Path:");
	ImGui::SameLine();
	ImGui::InputText("##pathName", (char*)path.c_str(), path.length(), ImGuiInputTextFlags_ReadOnly);

	ImGui::Text("Func:");
	ImGui::SameLine();
	ImGui::InputText("##funcName", (char*)func.c_str(), func.length(), ImGuiInputTextFlags_ReadOnly);
}

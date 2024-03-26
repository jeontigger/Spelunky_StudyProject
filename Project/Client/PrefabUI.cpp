#include "pch.h"
#include "PrefabUI.h"

#include <Engine\CPrefab.h>

#include "Inspector.h"

PrefabUI::PrefabUI()
	: AssetUI("Prefab", "##Prefab", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::render_update()
{
	AssetUI::render_update();

}

void PrefabUI::Activate()
{
	AssetUI::Activate();

	m_Prefab = (CPrefab*)GetAsset().Get();
	m_Inspector = (Inspector*)UIMGR->FindUI(UIInspectorName);
	
	m_Inspector->SetTargetObject(m_Prefab->GetProtoType());
}

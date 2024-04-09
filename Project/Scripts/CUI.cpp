#include "pch.h"
#include "CUI.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CDevice.h>

#include "CStage.h"

void CUI::SetScreenPos(Vec2 _vPos)
{
	m_vScreenPos = Vec3(_vPos.x, _vPos.y, UIZ);
}

void CUI::begin()
{
	GetOwner()->MeshRender()->setRenderActive(true);
	CStage* stage =(CStage*)CLevelMgr::GetInst()->GetCurrentLevel();
	CGameObject* camera = stage->GetUICamera();
	Vec3 vPos = camera->Transform()->GetRelativePos();
	Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();

	vPos.x -= vResolution.x/2.f * camera->Camera()->GetScale();
	vPos.y += vResolution.y/2.f * camera->Camera()->GetScale();
	vPos.x += m_vScreenPos.x;
	vPos.y -= m_vScreenPos.y;
	vPos.z = UIZ;

	GetOwner()->Transform()->SetRelativePos(vPos);
}

void CUI::tick()
{
}

CUI::CUI()
	:CScript((UINT)SCRIPT_TYPE::UI)
{
	
}

CUI::~CUI()
{
}

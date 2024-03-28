#include "pch.h"
#include "CCameraMovement.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>

#include <Engine/CMeshRender.h>
#include <Engine\CCamera.h>

CCameraMovement::CCameraMovement()
	: CScript(CAMERAMOVEMENT)
	, m_fSpeed(500)
{
}
CCameraMovement::~CCameraMovement()
{
}


void CCameraMovement::tick()
{
	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC) {
		auto pos = Transform()->GetRelativePos();
		m_vPrevPos = pos;
		if (KEY_PRESSED(KEY::W)) {
			pos.y += m_fSpeed * DT;
		}
		if (KEY_PRESSED(KEY::D)) {
			pos.x += m_fSpeed * DT;
		}
		if (KEY_PRESSED(KEY::A)) {
			pos.x -= m_fSpeed * DT;
		}
		if (KEY_PRESSED(KEY::S)) {
			pos.y -= m_fSpeed * DT;
		}
		m_vMoveDir = pos - m_vPrevPos;
		m_vMoveDir.Normalize();
		Transform()->SetRelativePos(pos);
	}
	else {
		Vec3 vPos = Transform()->GetRelativePos();

		Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);
		Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);

		if (KEY_PRESSED(KEY::W))
		{
			vPos += DT * m_fSpeed * vFront;
		}

		if (KEY_PRESSED(KEY::S))
		{
			vPos += DT * m_fSpeed * -vFront;
		}

		if (KEY_PRESSED(KEY::A))
		{
			vPos += DT * m_fSpeed * -vRight;
		}

		if (KEY_PRESSED(KEY::D))
		{
			vPos += DT * m_fSpeed * vRight;
		}

		Transform()->SetRelativePos(vPos);

		if (KEY_PRESSED(KEY::RBTN))
		{
			Vec2 vDrag = CKeyMgr::GetInst()->GetMouseDrag();
			Vec3 vRot = Transform()->GetRelativeRotation();
			vRot.y += vDrag.x * DT_ENGINE * XM_PI / 4.f;
			vRot.x += vDrag.y * DT_ENGINE * XM_PI / 4.f;
			Transform()->SetRelativeRotation(vRot);
		}
	}
}

void CCameraMovement::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CMeshRender* render = _OtherObj->MeshRender();
	if (render) {
		render->setRenderActive(true);
	}
	
}

void CCameraMovement::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetName() == CameraColliderWallName) {
		auto pos = Transform()->GetRelativePos();
		pos.x = m_vPrevPos.x;
		Transform()->SetRelativePos(pos);
	}

	if (_OtherObj->GetName() == CameraColliderPlatformName) {
		auto pos = Transform()->GetRelativePos();
		pos.y = m_vPrevPos.y;
		Transform()->SetRelativePos(pos);
	}
}

void CCameraMovement::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CMeshRender* render = _OtherObj->MeshRender();
	if (render) {
		render->setRenderActive(false);
	}

}


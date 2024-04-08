#include "pch.h"
#include "CCameraMovement.h"

#include <Engine/CKeyMgr.h>
#include <Engine/CTimeMgr.h>

#include <Engine/CMeshRender.h>
#include <Engine\CCamera.h>

CCameraMovement::CCameraMovement()
	: CScript((UINT)SCRIPT_TYPE::CAMERAMOVEMENT)
	, m_fSpeed(700)
{
	
}
CCameraMovement::~CCameraMovement()
{
}


void CCameraMovement::SetTarget(CGameObject* _target)
{
	m_Target = _target; 
	m_vTargetPos = Vec3(0.f, 0.f, 0.f);
}

void CCameraMovement::SetTarget(Vec3 _target)
{
	m_Target = nullptr;
	m_vTargetPos = _target;
}

void CCameraMovement::tick()
{
	if (m_Target) {
		Vec3 vPos = Transform()->GetRelativePos();
		Vec3 TargetPos = m_Target->Transform()->GetRelativePos();
		TargetPos.z = vPos.z;

		Vec3 Dir = TargetPos - vPos;
		if (m_bCameraWallBlocked) {
			TargetPos.x = 0;
		}

		if (m_bCameraPlatformBlocked) {
			TargetPos.y = 0;
		}
		if (Vec3::Distance(vPos, TargetPos) < 3.f) {
			return;
		}
		
		Dir.Normalize();

		vPos += Dir * m_fSpeed * DT;

		Transform()->SetRelativePos(vPos);
	}
	else if (m_vTargetPos != Vec3(0.f, 0.f, 0.f)) {
		Vec3 vPos = Transform()->GetRelativePos();
		m_vTargetPos.z = vPos.z;

		Vec3 Dir = m_vTargetPos - vPos;
		if (m_bCameraWallBlocked) {
			m_vTargetPos.x = 0;
		}

		if (m_bCameraPlatformBlocked) {
			m_vTargetPos.y = 0;
		}
		if (Vec3::Distance(vPos, m_vTargetPos) < 3.f) {
			return;
		}

		Dir.Normalize();

		vPos += Dir * m_fSpeed * DT;

		Transform()->SetRelativePos(vPos);
	}

	if (KEY_TAP(P)) {
		if (Collider2D()->GetOffsetScale() == CameraViewAll) {
			Collider2D()->SetOffsetScale(CameraViewNormal);
		}
		else {
			Collider2D()->SetOffsetScale(CameraViewAll);
		}
	}

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

#include "CFieldObject.h"

void CCameraMovement::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CMeshRender* render = _OtherObj->MeshRender();
	if (render) {
		render->setRenderActive(true);
	}
}

void CCameraMovement::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	m_bCameraWallBlocked = false;
	m_bCameraPlatformBlocked = false;
	if (_OtherObj->GetName() == CameraColliderWallName) {
		auto pos = Transform()->GetRelativePos();
		if (pos.x <= _OtherObj->Transform()->GetRelativePos().x) {
			pos.x = _OtherObj->Transform()->GetRelativePos().x - (Collider2D()->GetRelativeScale().x + _OtherObj->Transform()->GetRelativeScale().x) / 2.f -1.f;
		}
		else {
			pos.x = _OtherObj->Transform()->GetRelativePos().x + (Collider2D()->GetRelativeScale().x + _OtherObj->Transform()->GetRelativeScale().x) / 2.f + 1.f;
		}
		Transform()->SetRelativePos(pos);
		m_bCameraWallBlocked = true;
	}

	if (_OtherObj->GetName() == CameraColliderPlatformName) {
		auto pos = Transform()->GetRelativePos();
		if (pos.y <= _OtherObj->Transform()->GetRelativePos().y) {
			pos.y = _OtherObj->Transform()->GetRelativePos().y - (Collider2D()->GetRelativeScale().y + _OtherObj->Transform()->GetRelativeScale().y) / 2.f -1.f;
		}
		else {
			pos.y = _OtherObj->Transform()->GetRelativePos().y + (Collider2D()->GetRelativeScale().y + _OtherObj->Transform()->GetRelativeScale().y) / 2.f + 1.f;
		}
		Transform()->SetRelativePos(pos);
		m_bCameraPlatformBlocked = true;
	}
}

void CCameraMovement::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CMeshRender* render = _OtherObj->MeshRender();
	if (render) {
		render->setRenderActive(false);
	}
	if (_OtherObj->GetName() == CameraColliderWallName) {
		auto pos = Transform()->GetRelativePos();
	}
}


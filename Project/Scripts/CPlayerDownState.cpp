#include "pch.h"
#include "CPlayerDownState.h"

#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CPlayerScript.h"
#include "CPlayerHitCollider.h"
#include "CStage.h"
#include "CCameraMovement.h"

CPlayerDownState::CPlayerDownState()
	: CState((UINT)STATE_TYPE::PLAYERDOWNSTATE)
	, m_fCameraDown(1.f)
	, m_ChangeColliderPos(0.f, -0.2f)
	, m_ChangeColliderScale(1.3f, 0.5f)
	, m_fCrawlingSpeed(1.5f)
	, m_vChangeSocketPos(20.f, -40.f, HandleZ)
{

}

CPlayerDownState::~CPlayerDownState()
{
}

void CPlayerDownState::finaltick()
{
	// 일어나기
	if (KEY_RELEASED(m_Script->GetInputKeys().LookDown)) {
		ChangeState(StatePlayerIdle);
	}

	// 엎드린채로 떨어지기
	if (!m_Script->IsGrounded()) {
		ChangeState(StatePlayerFallDown);
	}


	if (KEY_TAP(m_Script->GetInputKeys().Bomb)) {
		m_Script->Bomb();
	}

	// 카메라 조절
	if (m_fCameraDownTimer < 0) {
		CStage* stage = (CStage*)CLevelMgr::GetInst()->GetCurrentLevel();
		Vec3 vPos = m_Player->Transform()->GetRelativePos();
		vPos.y -= 300.f;
		stage->GetMainCamera()->GetScript<CCameraMovement>()->SetTarget(vPos);
	}

	// 점프
	if (KEY_PRESSED(m_Script->GetInputKeys().Jump)) {
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0) {
			if (m_Script->IsGrounded())
				ChangeState(StatePlayerJumpUp);
		}
	}

	// 무빙
	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		m_Player->Animator2D()->Play(AnimPlayerCrawl);
		m_Script->TurnLeft();
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		m_Player->Animator2D()->Play(AnimPlayerCrawl);
		m_Script->TurnRight();
	}
	if (KEY_RELEASED(m_Script->GetInputKeys().MoveLeft)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveRight)) {
			m_Player->Animator2D()->Play(AnimPlayerCrawl);
			m_Script->TurnRight();
		}
		else {
			m_Player->Animator2D()->Play(AnimPlayerDownIdle, false);
		}
	}
	if (KEY_RELEASED(m_Script->GetInputKeys().MoveRight)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveLeft)) {
			m_Player->Animator2D()->Play(AnimPlayerCrawl);
			m_Script->TurnLeft();
		}
		else {
			m_Player->Animator2D()->Play(AnimPlayerDownIdle, false);
		}
	}

	if (m_Script->IsMoving()) {
		m_Script->MoveFront();
	}
	else {
		m_Script->Stop();
	}

	m_fCameraDownTimer -= DT;
}

void CPlayerDownState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_fCameraDownTimer = m_fCameraDown;
	m_Player->Animator2D()->Play(AnimPlayerDown, false);

	m_OriginColliderPos = m_Script->m_HitCollider->Collider2D()->GetOffsetPos();
	m_OriginColliderScale = m_Script->m_HitCollider->Collider2D()->GetOffsetScale();

	m_Script->m_HitCollider->Collider2D()->SetOffsetPos(m_ChangeColliderPos);
	m_Script->m_HitCollider->Collider2D()->SetOffsetScale(m_ChangeColliderScale);

	m_fOriginSpeed = m_Script->GetSpeed();
	m_Script->SetSpeed(m_fCrawlingSpeed);

	if (m_Script->IsMoving()) {
		m_Player->Animator2D()->Play(AnimPlayerCrawl);
	}

	m_vOriginSocketPos = m_Script->GetSocketPos();
	m_Script->SetSocketPos(m_vChangeSocketPos);
}

void CPlayerDownState::Exit()
{
	m_Script->m_HitCollider->Collider2D()->SetOffsetPos(m_OriginColliderPos);
	m_Script->m_HitCollider->Collider2D()->SetOffsetScale(m_OriginColliderScale);

	m_fCameraDownTimer = m_fCameraDown;

	CStage* stage = (CStage*)CLevelMgr::GetInst()->GetCurrentLevel();
	auto player = stage->FindObjectByName(L"Player");
	auto player2 = m_Player;
	auto player3 = (CGameObject*)GetBlackboardData(BBOwnerKey);
	stage->GetMainCamera()->GetScript<CCameraMovement>()->SetTarget(player);

	m_Script->SetSpeed(m_fOriginSpeed);

	m_Script->SetSocketPos(m_vOriginSocketPos);
}

#include "pch.h"
#include "CPlayerDownState.h"

#include <Engine/CGameObject.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CPlayerScript.h"
#include "CPlayerHitCollider.h"
#include "CStage.h"
#include "CCameraMovement.h"
#include "CMovement.h"

CPlayerDownState::CPlayerDownState()
	: CState((UINT)STATE_TYPE::PLAYERDOWNSTATE)
	, m_fCameraDown(1.f)
	, m_ChangeColliderPos(0.f, -0.2f)
	, m_ChangeColliderScale(1.3f, 0.5f)
	, m_fCrawlingSpeed(200.f)
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

	// 카메라 조절
	if (m_fCameraDownTimer < 0) {
		CStage* stage = (CStage*)CLevelMgr::GetInst()->GetCurrentLevel();
		Vec3 vPos = m_Player->Transform()->GetRelativePos();
		vPos.y -= 300.f;
		stage->GetMainCamera()->GetScript<CCameraMovement>()->SetTarget(vPos);
	}

	// 점프
	if (KEY_TAP((m_Script->GetInputKeys().Jump)) || KEY_PRESSED(m_Script->GetInputKeys().Jump)) {
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0) {
			ChangeState(StatePlayerJumpUp);
		}
	}

	PlayerKey input = m_Script->GetInputKeys();
	MovePriority priority = m_Script->GetMovePriority();

	// 좌우 움직임
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		if (KEY_TAP(input.MoveLeft)) {
			m_Script->TurnLeft();
			m_Player->Animator2D()->Play(AnimPlayerCrawl);
		}
		m_Movement->SetVelocityX(-m_Script->GetSpeed());
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		if (KEY_TAP(input.MoveRight)) {
			m_Player->Animator2D()->Play(AnimPlayerCrawl);
			m_Script->TurnRight();
		}
		m_Movement->SetVelocityX(m_Script->GetSpeed());
	}
	else {
		m_Movement->SetVelocityX(0);
		m_Player->Animator2D()->Play(ANIMPlayerDownIdle);
	}

	// 공격
	if (KEY_TAP(input.Attack)) {
		ChangeState(StatePlayerAttack);
	}

	m_fCameraDownTimer -= DT;
}

void CPlayerDownState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerDown, false);

	m_fCameraDownTimer = m_fCameraDown;

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

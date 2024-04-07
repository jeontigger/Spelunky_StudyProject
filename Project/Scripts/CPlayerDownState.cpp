#include "pch.h"
#include "CPlayerDownState.h"

#include <Engine/CGameObject.h>

#include "CPlayerScript.h"
#include "CPlayerHitCollider.h"

CPlayerDownState::CPlayerDownState()
	: CState((UINT)STATE_TYPE::PLAYERDOWNSTATE)
	, m_fCameraDown(1.f)
	, m_ChangeColliderPos(0.f, -0.2f)
	, m_ChangeColliderScale(1.3f, 0.5f)
{

}

CPlayerDownState::~CPlayerDownState()
{
}

void CPlayerDownState::finaltick()
{
	if (KEY_RELEASED(m_Script->GetInputKeys().LookDown) || KEY_NONE(m_Script->GetInputKeys().LookDown)) {
		ChangeState(StatePlayerIdle);
	}

	if (m_fCameraDownTimer < 0) {

	}

	if (KEY_PRESSED(m_Script->GetInputKeys().Jump)) {
		if (*(float*)GetBlackboardData(BBJumpDelay) < 0) {
			if (m_Script->IsGrounded())
				ChangeState(StatePlayerJumpUp);
		}
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		m_Script->TurnLeft();
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		m_Script->TurnRight();
	}

	if (m_Script->IsMoving()) {
		m_Script->MoveFront();
	}
	else {
		m_Script->Stop();
	}
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
}

void CPlayerDownState::Exit()
{
	m_Script->m_HitCollider->Collider2D()->SetOffsetPos(m_OriginColliderPos);
	m_Script->m_HitCollider->Collider2D()->SetOffsetScale(m_OriginColliderScale);
}

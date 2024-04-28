#include "pch.h"
#include "CPlayerJumpUpState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerJumpUpState::CPlayerJumpUpState()
	: CState((UINT)STATE_TYPE::PLAYERJUMPUPSTATE)
	, m_fJumpDelayTime(0.5f)
	, m_fJumpInitSpeed(800.7f)
	, m_fJumpMaxTime(.3f)
	, m_fJumpWeightSpeed(800.5f)
{
}

CPlayerJumpUpState::~CPlayerJumpUpState()
{
}

void CPlayerJumpUpState::Enter()
{
	// 멤버변수 갱신
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	// 애니메이션 출력
	m_Player->Animator2D()->Play(AnimPlayerJumpUp, false);

	// 점프 딜레이 갱신
	m_fJumpTimer = m_fJumpMaxTime;
	*(float*)GetBlackboardData(BBJumpDelay) = m_fJumpDelayTime;

	// 점프 추진력 추가
	m_Movement->SetVelocityY(m_fJumpInitSpeed);

}

void CPlayerJumpUpState::finaltick()
{
	m_Movement->SetVelocityX(0);

	auto input = m_Script->GetInputKeys();
	MovePriority priority = m_Script->GetMovePriority();

	if (m_fJumpTimer > 0) {
		if (KEY_PRESSED(input.Jump)) {
			m_Movement->AddForce(Vec3(0, m_fJumpWeightSpeed, 0));
		}
	}
	if(m_Script->IsGrounded() && (m_fJumpTimer != m_fJumpMaxTime)){
		if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
			ChangeState(StatePlayerWalkLeft);
		}
		else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
			ChangeState(StatePlayerWalkRight);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
		m_Script->CloudSpawn();
	}

	// 좌우 움직임
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		m_Script->TurnLeft();
		m_Movement->SetVelocityX(-m_Script->GetSpeed());
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		m_Script->TurnRight();
		m_Movement->SetVelocityX(m_Script->GetSpeed());
	}
	

	m_fJumpTimer -= DT;
}

void CPlayerJumpUpState::Exit()
{
}

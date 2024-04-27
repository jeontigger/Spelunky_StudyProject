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
	// ������� ����
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	// �ִϸ��̼� ���
	m_Player->Animator2D()->Play(AnimPlayerJumpUp, false);

	// ���� ������ ����
	m_fJumpTimer = m_fJumpMaxTime;
	*(float*)GetBlackboardData(BBJumpDelay) = m_fJumpDelayTime;

	// ���� ������ �߰�
	m_Movement->SetVelocityY(m_fJumpInitSpeed);

}

void CPlayerJumpUpState::finaltick()
{
	m_Movement->SetVelocityX(0);

	auto input = m_Script->GetInputKeys();

	if (m_fJumpTimer > 0) {
		if (KEY_PRESSED(input.Jump)) {
			m_Movement->AddForce(Vec3(0, m_fJumpWeightSpeed, 0));
		}
	}
	else {
		ChangeState(StatePlayerFallDown);
	}

	// �¿� ������
	MovePriority priority = m_Script->GetMovePriority();
	if (priority == MovePriority::Left && (KEY_TAP(input.MoveLeft) || KEY_PRESSED(input.MoveLeft))) {
		m_Movement->SetVelocityX(-m_Script->GetSpeed());
	}
	else if (priority == MovePriority::Right && (KEY_TAP(input.MoveRight) || KEY_PRESSED(input.MoveRight))) {
		m_Movement->SetVelocityX(m_Script->GetSpeed());
	}
	

	m_fJumpTimer -= DT;
}

void CPlayerJumpUpState::Exit()
{
}

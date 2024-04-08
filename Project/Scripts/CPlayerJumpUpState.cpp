#include "pch.h"
#include "CPlayerJumpUpState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerJumpUpState::CPlayerJumpUpState()
	: CState((UINT)STATE_TYPE::PLAYERJUMPUPSTATE)
	, m_fJumpDelayTime(0.5f)
	, m_fJumpInitSpeed(8.7f)
	, m_fJumpMaxTime(0.3f)
	, m_fJumpWeightSpeed(4.5f)
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

	// �ִϸ��̼� ���
	m_Player->Animator2D()->Play(AnimPlayerJumpUp, false);

	// ���� ������ ����
	m_fJumpTimer = m_fJumpMaxTime;
	*(float*)GetBlackboardData(BBJumpDelay) = m_fJumpDelayTime;

	// ���� ������ �߰�
	m_Script->SetVelocity(Vec2(0.f, m_fJumpInitSpeed));
	m_Script->SetGround(false);

	m_fJumpTimer = m_fJumpMaxTime;
}

void CPlayerJumpUpState::finaltick()
{
	if (m_fJumpTimer > 0) {
		m_Script->AddVelocity(Vec2(0.f, m_fJumpWeightSpeed * DT));
	}
	else {
		ChangeState(StatePlayerFallDown);
	}

	if (m_Script->IsGrounded()) {
		ChangeState(StatePlayerIdle);
	}

	PlayerMoveDefault;
}

void CPlayerJumpUpState::Exit()
{
}
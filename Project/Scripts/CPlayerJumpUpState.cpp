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
	// 멤버변수 갱신
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();

	// 애니메이션 출력
	m_Player->Animator2D()->Play(AnimPlayerJumpUp, false);

	// 점프 딜레이 갱신
	m_fJumpTimer = m_fJumpMaxTime;
	*(float*)GetBlackboardData(BBJumpDelay) = m_fJumpDelayTime;

	// 점프 추진력 추가
	m_Script->SetVelocity(Vec2(0.f, m_fJumpInitSpeed));
	m_Script->ClearGround();

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

	if (KEY_TAP(m_Script->GetInputKeys().Bomb)) {
		m_Script->Bomb();
	}

	// 사다리 타기
	if (KEY_PRESSED(m_Script->GetInputKeys().LookUp)) {
		if (m_Script->DetectLadder())
			ChangeState(StatePlayerLadder);
	}

	// 공격
	if (KEY_TAP(m_Script->GetInputKeys().Attack)) {
		// 채찍
		if (!m_Script->IsHandling()) {
			ChangeState(StatePlayerAttack);
		}
		// 던지기
		else {
			ChangeState(StatePlayerThrow);
		}
	}


	if (m_Script->IsGrounded()) {
		ChangeState(StatePlayerIdle);
		m_Script->CloudSpawn();
	}

	PlayerMoveDefault;
}

void CPlayerJumpUpState::Exit()
{
}

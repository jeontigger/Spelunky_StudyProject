#include "pch.h"
#include "CPlayerLadderState.h"

#include <Engine/CGameObject.h>
#include <Engine/CKeyMgr.h>

#include "CPlayerScript.h"

CPlayerLadderState::CPlayerLadderState()
	: CState((UINT)STATE_TYPE::PLAYERLADDERSTATE)
	, m_fPlayerLadderSpeed(300.f)
{
}

CPlayerLadderState::~CPlayerLadderState()
{
}

void CPlayerLadderState::finaltick()
{
	if (KEY_TAP(m_Script->GetInputKeys().LookDown) || KEY_TAP(m_Script->GetInputKeys().LookUp)) {
		m_Player->Animator2D()->Play(AnimPlayerLadder);
	}

	if (KEY_PRESSED(m_Script->GetInputKeys().LookUp)) {
		Vec3 vPos = m_Player->Transform()->GetRelativePos();
		vPos.y += m_fPlayerLadderSpeed * DT;
		m_Player->Transform()->SetRelativePos(vPos);
	}
	if (KEY_PRESSED(m_Script->GetInputKeys().LookDown)) {
		Vec3 vPos = m_Player->Transform()->GetRelativePos();
		vPos.y -= m_fPlayerLadderSpeed * DT;
		m_Player->Transform()->SetRelativePos(vPos);
	}


	if (KEY_NONE(m_Script->GetInputKeys().LookUp) && KEY_NONE(m_Script->GetInputKeys().LookDown)) {
		m_Player->Animator2D()->Stop();
	}
	
	if (m_Script->IsGrounded()) {
		ChangeState(StatePlayerIdle);
	}

	if (KEY_PRESSED(m_Script->GetInputKeys().Jump)) {
		ChangeState(StatePlayerJumpUp);
	}

	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		m_Script->TurnLeft();
	}
	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		m_Script->TurnRight();
	}
}

void CPlayerLadderState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Player->Animator2D()->Play(AnimPlayerLadder);

	Vec3 vLadderPos = m_Script->GetDetectLadderPos();
	Vec3 vPlayerPos = m_Player->Transform()->GetRelativePos();
	vPlayerPos.x = vLadderPos.x;
	vPlayerPos.y += 1.f;
	m_Player->Transform()->SetRelativePos(vPlayerPos);
	m_Script->UseGravity(false);

	m_Script->UseVelocityX(false);
	m_Script->UseVelocityY(false);
		

	if (KEY_PRESSED(m_Script->GetInputKeys().MoveLeft)) {
		m_Script->TurnLeft();
	}
	if (KEY_PRESSED(m_Script->GetInputKeys().MoveRight)) {
		m_Script->TurnRight();
	}
}

void CPlayerLadderState::Exit()
{
	m_Script->UseGravity(true);
	m_Script->UseVelocityX(true);
	m_Script->UseVelocityY(true);
}

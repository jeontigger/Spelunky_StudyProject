#include "pch.h"
#include "CPlayerWalkRightState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerWalkRightState::CPlayerWalkRightState()
	: CState((UINT)STATE_TYPE::PLAYERWALKLEFTSTATE)
{
}

CPlayerWalkRightState::~CPlayerWalkRightState()
{
}

void CPlayerWalkRightState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
	Vec3 vRotation = m_Player->Transform()->GetRelativeRotation();
	vRotation.y = 0;
	m_Player->Transform()->SetRelativeRotation(vRotation);
}

void CPlayerWalkRightState::finaltick()
{
	if (KEY_RELEASED(m_Script->GetInputKeys().MoveRight)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveLeft)) {
			ChangeState(StatePlayerWalkLeft);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
	}

	if (KEY_TAP(m_Script->GetInputKeys().MoveLeft)) {
		ChangeState(StatePlayerWalkLeft);
	}

	if (KEY_TAP(m_Script->GetInputKeys().Jump)) {
		ChangeState(StatePlayerJumpUp);
	}

	m_Movement->SetVelocityX(m_Script->GetSpeed());
}

void CPlayerWalkRightState::Exit()
{
}

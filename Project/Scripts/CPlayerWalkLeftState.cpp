#include "pch.h"
#include "CPlayerWalkLeftState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"
#include "CMovement.h"

CPlayerWalkLeftState::CPlayerWalkLeftState()
	: CState((UINT)STATE_TYPE::PLAYERWALKLEFTSTATE)
{
}

CPlayerWalkLeftState::~CPlayerWalkLeftState()
{
}

void CPlayerWalkLeftState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_Movement = m_Player->GetScript<CMovement>();

	m_Player->Animator2D()->Play(AnimPlayerWalk);
	Vec3 vRotation = m_Player->Transform()->GetRelativeRotation();
	vRotation.y = XM_PI;
	m_Player->Transform()->SetRelativeRotation(vRotation);
}

void CPlayerWalkLeftState::finaltick()
{
	if (KEY_RELEASED(m_Script->GetInputKeys().MoveLeft)) {
		if (KEY_PRESSED(m_Script->GetInputKeys().MoveRight)) {
			ChangeState(StatePlayerWalkRight);
		}
		else {
			ChangeState(StatePlayerIdle);
		}
	}

	if (KEY_TAP(m_Script->GetInputKeys().MoveRight)) {
		ChangeState(StatePlayerWalkRight);
	}

	m_Player->GetScript<CMovement>()->SetVelocityX(-m_Script->GetSpeed());
}

void CPlayerWalkLeftState::Exit()
{
	//m_Script->Stop();
}

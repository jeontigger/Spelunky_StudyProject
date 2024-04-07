#include "pch.h"
#include "CPlayerDownState.h"

#include <Engine/CGameObject.h>
#include "CPlayerScript.h"

CPlayerDownState::CPlayerDownState()
	: CState((UINT)STATE_TYPE::PLAYERDOWNSTATE)
	, m_fCameraDown(1.f)
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
}

void CPlayerDownState::Enter()
{
	m_Player = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_Script = m_Player->GetScript<CPlayerScript>();
	m_fCameraDownTimer = m_fCameraDown;
	m_Player->Animator2D()->Play(AnimPlayerDown, false);
}
#include "pch.h"
#include "CSnakeIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CTransform.h>

#include	"CSnakeScript.h"
#include "CSnakeAttackState.h"
#include "CMovement.h"

CSnakeIdleState::CSnakeIdleState()
	: CState((UINT)STATE_TYPE::SNAKEIDLESTATE)
	, m_pPlayer(nullptr)
{
	m_fDuration = 0.1f;
}

CSnakeIdleState::~CSnakeIdleState()
{
}

void CSnakeIdleState::finaltick()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pScript = m_pOwner->GetScript<CSnakeScript>();
	m_pPlayer = (CGameObject*)GetBlackboardData(StrPlayerName);
	m_Movement = m_pOwner->GetScript<CMovement>();


	if (m_pScript->DetectPlayer()) {
		auto state = GetFSM()->GetState<CSnakeAttackState>();
		ChangeState(CStateMgr::GetStateName(state));
	}

	if (m_pScript->IsGrounded()) {

		// 돌아야 한다면
		if (!m_pScript->DetectFrontTile() || m_pScript->DetectFrontWall()) {
			if (m_fDuration < m_fAccTime) {
				if (m_pScript->IsLookRight()) {
					m_pScript->TurnLeft();
				}
				else if (!m_pScript->IsLookRight()) {
					m_pScript->TurnRight();
				}
				m_fAccTime = 0.f;
			}
			m_fAccTime += DT;
		}

		// 기본 좌우 움직임
		if (m_pScript->IsLookRight()) {
			m_Movement->SetVelocityX(m_pScript->GetSpeed());
		}
		else {
			m_Movement->SetVelocityX(-m_pScript->GetSpeed());
		}
	}
}

void CSnakeIdleState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pOwner->Animator2D()->Play(AnimSnakeWalk);
}

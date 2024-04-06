#include "pch.h"
#include "CSnakeIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CTransform.h>

#include	"CSnakeScript.h"
#include "CSnakeAttackState.h"

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

	if (m_pScript->DetectPlayer()) {
		auto state = GetFSM()->GetState<CSnakeAttackState>();
		ChangeState(CStateMgr::GetStateName(state));
	}

	if (m_pScript->IsGrounded()) {
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
		m_pScript->MoveFront();
	}
}

void CSnakeIdleState::Enter()
{
	m_pOwner = (CGameObject*)GetBlackboardData(BBOwnerKey);
	m_pOwner->Animator2D()->Play(AnimSnakeWalk);
}

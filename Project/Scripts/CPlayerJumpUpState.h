#pragma once

#include <Engine/CState.h>

class CPlayerJumpUpState
	: public CState
{
private:
	class CGameObject* m_Player;
	class CPlayerScript* m_Script;
	class CMovement* m_Movement;

private:
	float m_fJumpInitSpeed;
	float m_fJumpWeightSpeed;
	float m_fJumpMaxTime;
	float m_fJumpTimer;
	float m_fJumpDelayTime;
	bool m_bJumpup;

public:
	virtual void Enter() override;
	virtual void finaltick() override;
	virtual void Exit() override;

public:
	CPlayerJumpUpState();
	~CPlayerJumpUpState();
};


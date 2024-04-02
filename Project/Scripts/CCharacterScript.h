#pragma once

#include "CFieldObject.h"

class CCharacterScript
	: public CFieldObject
{
private:
	bool m_bDead;

public:
	virtual void Die() {}
	virtual void Hit();

protected:
	bool m_bLastMoveDir; // 0 : left, 1 : right
	float m_fRunSpeed;
	bool m_bMoveLeft;
	bool m_bMoveRight;

public:
	void SetSpeed(float _speed) { m_fRunSpeed = _speed; }
	bool IsLookRight();
	void MoveLeft();
	void MoveRight();
	bool IsMoving() {
		return m_bMoveRight || m_bMoveLeft;
	}

public:
	virtual void tick() override;

public:
	CCharacterScript(UINT type);
	~CCharacterScript();
};


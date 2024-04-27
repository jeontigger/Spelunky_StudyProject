#pragma once

#include "CFieldObject.h"

class CCharacterScript
	: public CFieldObject
{
protected:
	CharacterInfo m_tInfo;

public:
	virtual void Die() { GamePlayStatic::DestroyGameObject(GetOwner()); }
	virtual void Hit(int _damage);

	void SetSpeed(float _speed) { m_tInfo.Speed = _speed; }
	float GetSpeed() { return m_tInfo.Speed; }

	void SetDamage(int _damage) { m_tInfo.Damage = _damage; }
	int GetDamage() { return m_tInfo.Damage; }

	void SetHealth(int _health) { m_tInfo.Health = _health; }
	int GetHealth() { return m_tInfo.Health; }

protected:
	bool m_bMoveFront;
	bool m_bMoveBack;

public:
	void Stop() { m_bMoveFront = false; m_bMoveBack = false; }
	bool IsLookRight();
	void TurnLeft();
	void TurnRight();
	void MoveFront();
	bool IsMoving() {
		return m_bMoveFront || m_bMoveBack;
	}

public:
	virtual void tick() override;
	virtual void begin() override;

public:
	CCharacterScript(UINT type);
	CCharacterScript(const CCharacterScript& _origin);
	~CCharacterScript();
};


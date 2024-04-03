#pragma once

#include "CFieldObject.h"

class CCharacterScript
	: public CFieldObject
{
private:
	CharacterInfo m_tInfo;

public:
	virtual void Die() { GamePlayStatic::DestroyGameObject(GetOwner()); }
	virtual void Hit(int _damage);

	void SetSpeed(float _speed) { m_tInfo.Speed = _speed; }
	int GetSpeed() { return m_tInfo.Speed; }

	void SetDamage(int _damage) { m_tInfo.Damage = _damage; }
	int GetDamage() { return m_tInfo.Damage; }

	void SetHealth(int _health) { m_tInfo.Health = _health; }
	int GetHealth() { return m_tInfo.Health; }

protected:
	bool m_bLastMoveDir; // 0 : left, 1 : right
	bool m_bMoveLeft;
	bool m_bMoveRight;

public:
	
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


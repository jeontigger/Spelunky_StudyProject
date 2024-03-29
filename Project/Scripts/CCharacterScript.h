#pragma once

#include "CFieldObject.h"

class CCharacterScript
	: public CFieldObject
{
private:
	bool m_bDead;

public:
	virtual void Die() {}

public:
	CCharacterScript(UINT type);
	~CCharacterScript();
};


#pragma once
#include "CFieldObject.h"
class CItem :
    public CFieldObject
{
private:
    class CPlayerScript* m_PlayerScript;

public:
    void SetPlayerScript(CPlayerScript* _player);

public:
    virtual void tick() override;

public:
    CLONE(CItem);
    CItem(UINT type);
    ~CItem();
};


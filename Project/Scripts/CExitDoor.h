#pragma once
#include <Engine/CScript.h>
class CExitDoor :
    public CScript
{
private:
    CGameObject* m_KeyTex;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CExitDoor);
    CExitDoor();
    ~CExitDoor();
};


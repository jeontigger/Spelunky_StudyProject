#pragma once
#include <Engine\CLevel.h>
class CTitleLevel :
    public CLevel
{
private:
    CGameObject* m_MainCamera;

public:
    virtual void tick() override;
    virtual void begin() override;

public:
    CTitleLevel();
    ~CTitleLevel();
};


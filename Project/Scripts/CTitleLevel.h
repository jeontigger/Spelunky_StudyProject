#pragma once
#include <Engine\CLevel.h>

enum class TitleLevelState {
    AnyKeyPress,
    Select,
};
class CTitleLevel :
    public CLevel
{
private:
    TitleLevelState m_State;

    CGameObject* m_MainCamera;

public:
    virtual void tick() override;
    virtual void begin() override;

public:
    CTitleLevel();
    ~CTitleLevel();

private:
    void ChangeLevelState(TitleLevelState _state);
};


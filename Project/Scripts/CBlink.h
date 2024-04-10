#pragma once
#include <Engine\CScript.h>
class CBlink :
    public CScript
{
private:
    float m_fOnTime;
    float m_fOffTime;
    float m_fOnTimer;
    float m_fOffTimer;

public:
    void Set(float _on, float _off) { m_fOnTime = _on, m_fOffTime = _off; }
    void Set(float _time) { m_fOnTime = _time; m_fOffTime = _time; }

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CBlink);
    CBlink();
    ~CBlink();
};


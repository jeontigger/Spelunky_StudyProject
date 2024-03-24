#pragma once
#include "UI.h"
class AddComponentUI :
    public UI
{
private:
    class CGameObject* m_target;
    vector<string> m_vecComponentStrings;
public:
    inline void SetTargetObject(CGameObject* _target) { m_target = _target; }

public:
    virtual void render_update() override;

public:
    AddComponentUI();
    ~AddComponentUI();
};


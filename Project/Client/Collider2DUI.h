#pragma once
#include "ComponentUI.h"
class Collider2DUI :
    public ComponentUI
{
private:
    class CCollider2D* m_collider;

public:
    virtual void Activate() override;
    virtual void render_update() override;

public:
    Collider2DUI();
    ~Collider2DUI();
};


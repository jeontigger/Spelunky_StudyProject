#pragma once
#include "ComponentUI.h"

#include <Engine/CCamera.h>

class CameraUI :
    public ComponentUI
{
private:
    CCamera* m_camera;

public:
    virtual void Activate() override;
    virtual void render_update() override;

public:
    CameraUI();
    ~CameraUI();
};


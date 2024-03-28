#pragma once
#include "CRenderComponent.h"
class CMeshRender :
    public CRenderComponent
{
private:
    bool m_bRenderActive;

public:
    bool isRenderActive() { return m_bRenderActive; }
    void setRenderActive(bool _state) { m_bRenderActive = _state; }

public:
    virtual void UpdateData() override;
    virtual void finaltick() override;
    virtual void render() override;
     
    CLONE(CMeshRender);
public:
    CMeshRender();
    ~CMeshRender();
};


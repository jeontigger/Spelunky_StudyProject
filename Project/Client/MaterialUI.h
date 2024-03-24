#pragma once
#include "AssetUI.h"
class MaterialUI :
    public AssetUI
{
private:
    TEX_PARAM       m_SelectTexParam;
    Ptr<CMaterial> m_Mtrl;

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    void SelectTexture(DWORD_PTR _dwData);

public:
    MaterialUI();
    ~MaterialUI();


private:
    void GraphicsShaderSelect(DWORD_PTR _ptr);
};


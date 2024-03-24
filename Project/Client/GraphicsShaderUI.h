#pragma once
#include "AssetUI.h"



class GraphicsShader :
    public AssetUI
{
private:
    class CGraphicsShader* m_shader;

private:
    void DisplayInfo(const string& path, const string& func);

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    GraphicsShader();
    ~GraphicsShader();
};


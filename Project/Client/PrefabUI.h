#pragma once
#include "AssetUI.h"

class PrefabUI :
    public AssetUI
{
private:
    Ptr<CPrefab> m_Prefab;
    class Inspector* m_Inspector;

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    PrefabUI();
    ~PrefabUI();
};


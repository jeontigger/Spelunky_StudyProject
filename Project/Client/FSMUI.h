#pragma once
#include "AssetUI.h"

class FSMUI :
    public AssetUI
{
private:
    Ptr<CFSM> m_target;
    vector<string> m_vecNames;

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    FSMUI();
    ~FSMUI();

private:
    void CurState();
    void StateList();
    void AddState();
};


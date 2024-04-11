#pragma once
#include <Engine/CScript.h>

class CUI :
    public CScript
{
private:
    Vec3 m_vScreenPos;

public:
    void SetScreenPos(Vec2 _vPos);
    Vec2 GetScreenPos() { return Vec2(m_vScreenPos.x, m_vScreenPos.y); }

public:
    virtual void begin() override;
    virtual void tick() override {}
    virtual void finaltick() override;

    virtual void SaveToFile(FILE* _File) {}
    virtual void SaveToFile(ofstream& _File) {}
    virtual void LoadFromFile(FILE* _File) {}
    virtual void LoadFromFile(ifstream& _File) {}

public:
    CLONE(CUI);
    CUI();
    ~CUI();
};


#pragma once
#include <Engine/CLevel.h>

class PhysicsTest :
    public CLevel
{
private:
    std::unique_ptr<class b2World> m_world;
    CGameObject* m_MainCamera;
    CGameObject* m_obj;

private:
    ofstream m_file;
    class b2Body* m_body;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    PhysicsTest();
    ~PhysicsTest();
};


#pragma once

#include <Engine/CScript.h>

class CFieldObject :
    public CScript
{
private:
    UINT m_iMass;
    int m_iGravity;

public:
    inline void SetMass(UINT _mass) { m_iMass = _mass; }
    inline UINT GetMass() { return m_iMass; }

    inline void SetGravity(int _gravity) { m_iGravity = _gravity; }
    inline int GetGravity() { return m_iGravity; }

    inline bool IsMove() { return m_iGravity != 0; }

public:
    virtual void skill() = 0;

public:
    CFieldObject(UINT type);
    ~CFieldObject();
};


#pragma once
#include "CItem.h"
class CRock :
    public CItem
{

public:
    virtual void begin() override;

public:
    CLONE(CRock);
    CRock();
    ~CRock();
};


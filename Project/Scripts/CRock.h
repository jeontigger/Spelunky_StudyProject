#pragma once
#include "CItem.h"
class CRock :
    public CItem
{
public:
    CLONE(CRock);
    CRock();
    ~CRock();
};


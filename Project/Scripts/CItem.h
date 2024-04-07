#pragma once
#include "CFieldObject.h"
class CItem :
    public CFieldObject
{
public:
    CLONE(CItem);
    CItem(UINT type);
    ~CItem();
};


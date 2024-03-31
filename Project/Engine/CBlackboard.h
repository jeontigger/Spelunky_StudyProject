#pragma once
#include "CEntity.h"

enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;
    void*       pData;
};

class CBlackboard :
    public CEntity
{
private:
    map<wstring, tBlackboardData>   m_mapBBData;

public:
    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data);
    void* GetBlackboardData(const wstring& _strKey);

public:
    void Save(ofstream& fout);
    void Load(ifstream& fin);
    static void (*SaveGameObject)(class CGameObject* _Obj, ofstream& fout);
    static class CGameObject* (*LoadGameObject)(ifstream& fin);

public:
    void Copy(CBlackboard& _bb)const;
    CLONE(CBlackboard);
    CBlackboard();
    CBlackboard(const CBlackboard& _board);
    ~CBlackboard();

    friend class StateMachineUI;
};


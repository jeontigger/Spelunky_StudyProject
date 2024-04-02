#pragma once
#include "CCharacterScript.h"
class CSnakeScript
	: public CCharacterScript
{
private:
    class CMonsterDetectCollider* m_DetectTileCollider;
    class CMonsterDetectCollider* m_DetectWallAndPlayerCollider;

public:
    bool DetectFrontTile();
    bool DetectFrontWall();
    bool DetectPlayer();

public:
    virtual void begin() override;
    virtual void skill() {};

public:
    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};

public:
    CLONE(CSnakeScript);
	CSnakeScript();
	~CSnakeScript();
};


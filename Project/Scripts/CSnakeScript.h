#pragma once
#include "CCharacterScript.h"
class CSnakeScript
	: public CCharacterScript
{
private:
    class CMonsterHitCollider* m_HitCollider;
    class CDetectCollider* m_DetectTileCollider;
    class CDetectCollider* m_DetectWallAndPlayerCollider;

public:
    bool DetectFrontTile();
    bool DetectFrontWall();
    bool DetectPlayer();

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void skill() {};

public:
    virtual void SaveToFile(FILE* _File) {};
    virtual void SaveToFile(ofstream& _File) {};
    virtual void LoadFromFile(FILE* _File) {};
    virtual void LoadFromFile(ifstream& _File) {};

public:
    CLONE(CSnakeScript);
	CSnakeScript();
    CSnakeScript(const CSnakeScript& _origin);
	~CSnakeScript();
};


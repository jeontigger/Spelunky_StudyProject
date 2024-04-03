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

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

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


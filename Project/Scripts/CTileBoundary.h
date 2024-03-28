#pragma once
#include <Engine/CScript.h>


class CTileBoundary
	: public CScript
{
private:
	BoundaryTile m_Type;

public:
	void SetType(BoundaryTile type);

public:
	virtual void tick() {};
	virtual void begin() {};

	virtual void skill() {};

	virtual void SaveToFile(FILE* _File) {};
	virtual void SaveToFile(ofstream& _File) {};
	virtual void LoadFromFile(FILE* _File) {};
	virtual void LoadFromFile(ifstream& _File) {};

	CLONE(CTileBoundary);
public:
	CTileBoundary();
	~CTileBoundary();
};


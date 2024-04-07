#include "pch.h"
#include "CRock.h"

void CRock::begin()
{
	CItem::begin();

	Animator2D()->Play(AnimRock);
}

CRock::CRock()
	: CItem((UINT)SCRIPT_TYPE::ROCK)
{
}

CRock::~CRock()
{
}

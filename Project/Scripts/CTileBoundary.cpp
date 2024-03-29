#include "pch.h"
#include "CTileBoundary.h"

CTileBoundary::CTileBoundary()
	: CScript((UINT)SCRIPT_TYPE::TILEBOUNDARY)
	, m_Type(BoundaryTile::END)
{
}

CTileBoundary::~CTileBoundary()
{
}

void CTileBoundary::SetType(BoundaryTile type)
{
	switch (type)
	{
	case BoundaryTile::TOP:
		
		break;
	case BoundaryTile::RIGHT:
		break;
	case BoundaryTile::BUTTOM:
		break;
	case BoundaryTile::LEFT:
		break;
	case BoundaryTile::END:
		break;
	default:
		break;
	}
}

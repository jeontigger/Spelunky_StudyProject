#include "pch.h"
#include "CTile.h"

CTile::CTile(TileType type)
	:CFieldObject(SCRIPT_TYPE::TILE)
	, m_type(type)
{
}

CTile::~CTile()
{
}

void CTile::tick()
{

}


#include "pch.h"
#include "CTile.h"

CTile::CTile()
	:CFieldObject(SCRIPT_TYPE::TILE)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
}

CTile::CTile(const CTile& tile)
	:CFieldObject(SCRIPT_TYPE::TILE)
	, m_type(tile.m_type)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
	for (int i = 0; i < (int)SurroundTile::END; i++) {
		m_arrSurroundTiles[i] = tile.m_arrSurroundTiles[i];
	}
}

CTile::~CTile()
{
}

void CTile::SetTileType(TileType type)
{
	m_type = type;
	GetOwner()->DMtrlSetScalar(INT_0, type);

	Vec2 pos = TypeToPos(type);
	GetOwner()->DMtrlSetScalar(INT_1, (int)pos.x);
	GetOwner()->DMtrlSetScalar(INT_2, (int)pos.y);
	auto mtrl = GetOwner()->GetRenderComopnent()->GetDynamicMaterial();

	int a = 0;
}

void CTile::tick()
{
	static TileType prev = m_type;

	if (m_type != prev) {
		SetTileType(m_type);
	}
	prev = m_type;

}

void CTile::begin()
{

}

Vec2 CTile::TypeToPos(TileType type)
{
	switch (type)
	{
	case TileType::Blank:
		return Vec2(0, 0);
		break;
	case TileType::Soil:
		return Vec2(0, 1);

	case TileType::Tree:
		return Vec2(0, 2);
		break;
	case TileType::NeverCrash:
		return Vec2(0, 3);

	case TileType::Ladder:
		return Vec2(0, 4);

	case TileType::LadderHalf:
		return Vec2(0, 5);

	case TileType::Movable:
		break;
	case TileType::Spike:
		break;
	case TileType::Door:
		break;
	case TileType::END:
		break;
	default:
		break;
	}
}

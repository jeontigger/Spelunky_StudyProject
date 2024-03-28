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

void CTile::Instancing(TileType type, int row, int col)
{
	SetTileType(type);
	Vec3 pos = Vec3(row, col, 200.f);
	if (type == TileType::Door) {
		pos.x += TileScaleX;
		pos.y -= TileScaleY/2;
	}
	GetOwner()->Transform()->SetRelativePos(pos);
}

void CTile::SetTileType(TileType type)
{
	m_type = type;
	GetOwner()->DMtrlSetScalar(INT_0, type);

	Vec2 pos = TypeToPos(type);
	GetOwner()->DMtrlSetScalar(INT_1, (int)pos.x);
	GetOwner()->DMtrlSetScalar(INT_2, (int)pos.y);
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
	SetTileType(TileType::Blank);
}

Vec2 CTile::TypeToPos(TileType type)
{
	switch (type)
	{
	case TileType::Blank:
		return Vec2(1, 7);

	case TileType::Soil:
		return Vec2(0, 1);

	case TileType::Tree:
		return Vec2(2, 7);
		break;
	case TileType::NeverCrash:
		return Vec2(0, 0);
		break;
	case TileType::Ladder:
		return Vec2(1, 4);

	case TileType::LadderHalf:
		return Vec2(2, 4);

	case TileType::Movable:
		return Vec2(0, 7);
		break;
	case TileType::Spike:
		return Vec2(9, 5);
		break;

	case TileType::Door:
		return Vec2(7, 0);
		break;
	case TileType::END:
		break;
	default:
		break;
	}
}

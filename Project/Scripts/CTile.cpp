#include "pch.h"
#include "CTile.h"

int CTile::TileCount = 0;
CTile::CTile()
	:CFieldObject((UINT)SCRIPT_TYPE::TILE)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
}

CTile::CTile(const CTile& tile)
	:CFieldObject((UINT)SCRIPT_TYPE::TILE)
	, m_type(tile.m_type)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
	for (int i = 0; i < (int)BoundaryTile::END; i++) {
		m_arrSurroundTiles[i] = tile.m_arrSurroundTiles[i];
	}
}

CTile::~CTile()
{
}

void CTile::Instancing(TileType type, int row, int col)
{
	SetTileType(type);
	Vec3 pos = Vec3(row, col, TileZ);
	if (type == TileType::Door) {
		pos.x += TileScaleX;
		pos.y -= TileScaleY/2;
	}
	GetOwner()->Transform()->SetRelativePos(pos);
	TileCount++;
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
	TileCount;
}

void CTile::begin()
{
	SetTileType(TileType::Blank);
}

#include "CFieldObject.h"
void CTile::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

	auto script = _OtherObj->GetScript<CFieldObject>();
	if (script) {
		auto tilemat = _Collider->GetColliderWorldMat();
		auto objmat = _OtherCollider->GetColliderWorldMat();

		Vec3 tilePos(tilemat._41, tilemat._42, tilemat._43);
		Vec3 tileScale(tilemat._11, tilemat._22, tilemat._33);
		Vec3 objColPos(objmat._41, objmat._42, objmat._43);
		Vec3 objColScale(objmat._11, objmat._22, objmat._33);

		Vec3 objPos = _OtherObj->Transform()->GetRelativePos();
		Vec2 objVel = script->GetVelocity() * DT;
		Vec3 prevPos = Vec3(objPos.x - objVel.x, objPos.y - objVel.y, objPos.z);

		float deltaY = prevPos.y - (objColScale.y/2.f + tilePos.y);

		if (deltaY > 0) {
			objPos.y = tilePos.y + tileScale.y / 2.f;
			_OtherObj->Transform()->SetRelativePos(objPos);
		}

	}
	
}

void CTile::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {
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

	case TileType::Half:
		return Vec2(1, 1);

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

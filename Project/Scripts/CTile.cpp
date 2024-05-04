#include "pch.h"
#include "CTile.h"

#include "CTileMgr.h"

int CTile::TileCount = 0;
CTile::CTile()
	:CFieldObject((UINT)SCRIPT_TYPE::TILE)
	, m_PermitRange(2.f)
	, m_arrSurroundTiles{}
	, m_fReflectScale(3000.f)
	, m_fReflectWallScale(700.f)
	, m_fReflectReduceScale(0.7f)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
}

CTile::CTile(const CTile& tile)
	:CFieldObject((UINT)SCRIPT_TYPE::TILE)
	, m_type(tile.m_type)
	, m_PermitRange(2.f)
	, m_arrSurroundTiles{}
	, m_fReflectScale(3000.f)
	, m_fReflectReduceScale(0.7f)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Type", &m_type);
}

CTile::~CTile()
{
}

void CTile::Instancing(TileType type, int row, int col)
{
	SetTileType(type);
	Vec3 pos = Vec3((float)col, (float)row, TileZ);
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

	//if (m_type != TileType::Soil) return;
	//Vec2 Idx = CTileMgr::GetInst()->PosToIdx(GetOwner()->Transform()->GetRelativePos());
	//for (int i = 0; i < (UINT)TileDir::END; i++) {
	//	int nRow = Idx.x + nrow[i];
	//	int nCol = Idx.y + ncol[i];
	//	if(0 <= nRow && nRow < STAGETILEROW * TILEBLOCKSIZEY && 0 <= nCol && nCol < STAGETILECOL * TILEBLOCKSIZEX)
	//	{
	//		auto tile = CTileMgr::GetInst()->GetTile(Vec2(nCol, nRow));
	//		if (tile) {
	//			m_arrSurroundTiles[i]->Collider2D()->Activate(false);
	//		}
	//		else {
	//			m_arrSurroundTiles[i]->Collider2D()->Activate(true);
	//		}
	//		
	//	}
	//}
}

void CTile::begin()
{
	//SetTileType(TileType::Blank);

	//CGameObject* obj;
	//obj = m_arrSurroundTiles[(UINT)TileDir::TOP] = CAssetMgr::GetInst()->Load<CPrefab>(TileUp1PrefKey, TileUp1PrefKey)->Instantiate();
	//obj->Animator2D()->Play(AnimTileUp1);
	//GetOwner()->AddChild(obj);
	//GamePlayStatic::SpawnGameObject(obj, TileAroundLayer);

	//obj = m_arrSurroundTiles[(UINT)TileDir::RIGHT] = CAssetMgr::GetInst()->Load<CPrefab>(TileSideRight1PrefKey, TileSideRight1PrefKey)->Instantiate();
	//obj->Animator2D()->Play(AnimTileSideRight1);
	//GetOwner()->AddChild(obj);
	//GamePlayStatic::SpawnGameObject(obj, TileAroundLayer);

	//obj = m_arrSurroundTiles[(UINT)TileDir::LEFT] = CAssetMgr::GetInst()->Load<CPrefab>(TileSideRight1PrefKey, TileSideRight1PrefKey)->Instantiate();
	//obj->Animator2D()->Play(AnimTileSideRight1);
	//Vec3 rot = obj->Transform()->GetRelativeRotation();
	//rot.y = XM_PI;
	//obj->Transform()->SetRelativeRotation(rot);
	//Vec3 pos = obj->Transform()->GetRelativePos();
	//pos.x = -64.f;
	//obj->Transform()->SetRelativePos(pos);
	//GetOwner()->AddChild(obj);
	//GamePlayStatic::SpawnGameObject(obj, TileAroundLayer);

	//obj = m_arrSurroundTiles[(UINT)TileDir::BOTTOM] = CAssetMgr::GetInst()->Load<CPrefab>(TileBottom1PrefKey, TileBottom1PrefKey)->Instantiate();
	//obj->Animator2D()->Play(AnimTileBottom1);
	//GetOwner()->AddChild(obj);
	//GamePlayStatic::SpawnGameObject(obj, TileAroundLayer);

	//for (int i = 0; i < (UINT)TileDir::END; i++) {
	//	if (m_type != TileType::Soil)
	//		m_arrSurroundTiles[i]->Collider2D()->Activate(false);
	//}

}

#include "CFieldObject.h"
#include "CPlayerScript.h"
#include "CMovement.h"

void CTile::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

	auto fieldobjScript = _OtherObj->GetScript<CFieldObject>();
	auto movementScript = _OtherObj->GetScript<CMovement>();

	if (!fieldobjScript || !movementScript) return;

	// Platform 
	Vec3 TileColPos;
	Vec2 TileColScale;
	Vec2 TileLT, TileRB;
	TileColPos = _Collider->GetFinalPos();
	TileColScale = _Collider->GetFinalScale();

	TileLT = Vec2(TileColPos.x - TileColScale.x / 2.f, TileColPos.y + TileColScale.y / 2.f);
	TileRB = Vec2(TileColPos.x + TileColScale.x / 2.f, TileColPos.y - TileColScale.y / 2.f);

	// Object
	Vec3 ObjColPos;
	Vec3 ObjPrevPos;
	Vec2 ObjColScale;

	// Object Collider의 PrevPos
	ObjColPos = _OtherCollider->GetFinalPos();
	ObjPrevPos = ObjColPos - movementScript->GetVelocity() * DT;
	ObjColScale = _OtherCollider->GetFinalScale();

	MovementDir ObjDir = movementScript->GetDir();

	// 위에서 아래로 충돌
	if ((ObjDir & (MovementDir)MoveDir::DOWN) && TileLT.y < ObjPrevPos.y - ObjColScale.y / 2.f)
	{
		// Left 충돌
		if (TileLT.x >= ObjPrevPos.x + ObjColScale.x / 2.f)
		{
			LeftCollision(_OtherObj, TileLT.x, ObjColScale.x);
		}
		// Right 충돌
		else if (TileRB.x <= ObjPrevPos.x - ObjColScale.x / 2.f)
		{
			RightCollision(_OtherObj, TileRB.x, ObjColScale.x);
		}
		else {
			UpCollision(_OtherObj, TileLT.y, ObjColScale.y);

			if (_OtherObj->GetScript<CPlayerScript>()) {
				_OtherObj->GetScript<CPlayerScript>()->CloudSpawn();
			}
		}
	}
	// 아래서 위로 충돌
	else if ((ObjDir & (MovementDir)MoveDir::UP) && TileRB.y >= ObjPrevPos.y + ObjColScale.y / 2.f)
	{
		// Left 충돌
		if (TileLT.x >= ObjPrevPos.x + ObjColScale.x / 2.f)
		{
			LeftCollision(_OtherObj, TileLT.x, ObjColScale.x);
		}
		// Right 충돌
		else if (TileRB.x <= ObjPrevPos.x - ObjColScale.x / 2.f)
		{
			RightCollision(_OtherObj, TileRB.x, ObjColScale.x);
		}
		else {
			DownCollision(_OtherObj, TileRB.y, ObjColScale.y);
		}
	}
	else
	{
		// 허용 범위안에서 플랫폼을 넘어갈 때
		if ((TileLT.y - m_PermitRange < ObjPrevPos.y - ObjColScale.y / 2.f) && (TileLT.y + m_PermitRange > ObjPrevPos.y - ObjColScale.y / 2.f))
		{
			UpCollision(_OtherObj, TileLT.y, ObjColScale.y);
		}
		else
		{
			// Left 충돌
			if ((ObjDir & (MovementDir)MoveDir::RIGHT) && TileLT.x >= ObjPrevPos.x + ObjColScale.x / 2.f)
			{
				LeftCollision(_OtherObj, TileLT.x, ObjColScale.x);
			}
			// Right 충돌
			else if ((ObjDir & (MovementDir)MoveDir::LEFT) && TileRB.x - TileColScale.x/2.f <= ObjPrevPos.x - ObjColScale.x / 2.f)
			{
				RightCollision(_OtherObj, TileRB.x, ObjColScale.x);
			}
		}
	}

}

void CTile::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	auto fieldobjScript = _OtherObj->GetScript<CFieldObject>();
	auto movementScript = _OtherObj->GetScript<CMovement>();

	if (!fieldobjScript || !movementScript) return;

	// Platform 
	Vec3 TileColPos;
	Vec2 TileColScale;
	Vec2 TileLT, TileRB;
	TileColPos = _Collider->GetFinalPos();
	TileColScale = _Collider->GetFinalScale();

	TileLT = Vec2(TileColPos.x - TileColScale.x / 2.f, TileColPos.y + TileColScale.y / 2.f);
	TileRB = Vec2(TileColPos.x + TileColScale.x / 2.f, TileColPos.y - TileColScale.y / 2.f);

	// Object
	Vec3 ObjColPos;
	Vec3 ObjPrevPos;
	Vec2 ObjColScale;

	// Object Collider의 PrevPos
	//ObjPrevPos = _OtherObj->Collider2D()->GetPrevFinalPos();
	ObjColPos = _OtherCollider->GetFinalPos();
	ObjPrevPos = ObjColPos - movementScript->GetVelocity() * DT;
	ObjColScale = _OtherCollider->GetFinalScale();

	MovementDir ObjDir = movementScript->GetDir();

	// 아래서 위 충돌
	if ((ObjDir & (MovementDir)MoveDir::UP) && TileRB.y >= ObjPrevPos.y + ObjColScale.y / 2.f)
	{
		DownCollision(_OtherObj, TileRB.y, ObjColScale.y);
	}

	if (!fieldobjScript->IsOverlapGround(GetOwner())) {

		// 허용 범위안에서 플랫폼을 넘어갈 때
		if ((TileLT.y  <= ObjPrevPos.y - ObjColScale.y / 2.f) && (TileLT.y >= ObjPrevPos.y - ObjColScale.y / 2.f))
		{
			UpCollision(_OtherObj, TileLT.y, ObjColScale.y);
		}
		// Left 충돌
		else if ((ObjDir & (MovementDir)MoveDir::RIGHT) && TileLT.x >= ObjPrevPos.x + ObjColScale.x / 2.f)
		{
			LeftCollision(_OtherObj, TileLT.x, ObjColScale.x);
		}
		// Right 충돌
		else if ((ObjDir & (MovementDir)MoveDir::LEFT) && TileRB.x <= ObjPrevPos.x - ObjColScale.x / 2.f)
		{
			RightCollision(_OtherObj, TileRB.x, ObjColScale.x);
		}
	}
}
void CTile::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {

	auto fieldobjScript = _OtherObj->GetScript<CFieldObject>();
	auto movementScript = _OtherObj->GetScript<CMovement>();

	if (!fieldobjScript || !movementScript) return;

	fieldobjScript->SubOverlapGround(GetOwner());

	if (!fieldobjScript->IsGrounded())
	{
		movementScript->SetGround(false);
	}
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
	case TileType::ExitDoor:
		return Vec2(7, 0);
			break;
	case TileType::END:
		break;
	default:
		break;
	}

	return Vec2(0, 0);
}

void CTile::UpCollision(CGameObject* _Obj, float _PlatformTop, float _ObjColScaleY)
{
	Vec3 vVel = _Obj->GetScript<CMovement>()->GetVelocity();
	if (m_fReflectScale < vVel.y) {
		vVel.y = abs(vVel.y) * m_fReflectReduceScale;
		_Obj->GetScript<CMovement>()->SetVelocity(vVel);

		return;
	}

	float NewY = _PlatformTop + _ObjColScaleY / 2.f;
	NewY -= _Obj->Collider2D()->GetRelativePos().y ;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.y = NewY;

	_Obj->Transform()->SetRelativePos(ObjPos);

	CFieldObject* FieldObjectScript = _Obj->GetScript<CFieldObject>();
	FieldObjectScript->AddOverlapGround(GetOwner());

	if (FieldObjectScript->IsGrounded())
	{
		_Obj->GetScript<CMovement>()->SetGround(true);
	}
}

void CTile::DownCollision(CGameObject* _Obj, float _PlatformBottom, float _ObjColScaleY)
{
	Vec3 vVel = _Obj->GetScript<CMovement>()->GetVelocity();

	vVel.y = -abs(vVel.y);
	_Obj->GetScript<CMovement>()->SetVelocity(vVel);


	float NewY = _PlatformBottom - _ObjColScaleY / 2.f;
	NewY -= _Obj->Collider2D()->GetRelativePos().y;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.y = NewY;

	_Obj->Transform()->SetRelativePos(ObjPos);
}

void CTile::LeftCollision(CGameObject* _Obj, float _PlatformLeft, float _ObjColScaleX)
{
	Vec3 vVel = _Obj->GetScript<CMovement>()->GetVelocity();
	if (m_fReflectWallScale < abs(vVel.x)) {
		vVel.x = -abs(vVel.x) * m_fReflectReduceScale;
		_Obj->GetScript<CMovement>()->SetVelocity(vVel);

		return;
	}

	float NewX = _PlatformLeft - _ObjColScaleX / 2.f;
	NewX -= _Obj->Collider2D()->GetRelativePos().x;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.x = NewX;

	_Obj->Transform()->SetRelativePos(ObjPos);
}

void CTile::RightCollision(CGameObject* _Obj, float _PlatformRight, float _ObjColScaleX)
{
	Vec3 vVel = _Obj->GetScript<CMovement>()->GetVelocity();
	if (m_fReflectWallScale < abs(vVel.x)) {
		vVel.x = abs(vVel.x) * m_fReflectReduceScale;
		_Obj->GetScript<CMovement>()->SetVelocity(vVel);

		return;
	}

	float NewX = _PlatformRight + _ObjColScaleX / 2.f;
	NewX -= _Obj->Collider2D()->GetRelativePos().x;

	Vec3 ObjPos = _Obj->Transform()->GetRelativePos();
	ObjPos.x = NewX;

	_Obj->Transform()->SetRelativePos(ObjPos);
}

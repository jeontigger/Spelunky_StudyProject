#include "pch.h"
#include "CTileMgr.h"

#include "CTile.h"

void CTileMgr::CheckLayer(UINT _layer)
{
	m_LayerCheck |= (1 << _layer);
}

Vec3 CTileMgr::GetEntrancePos()
{
	for (int blockCol = 0; blockCol < STAGETILECOL; blockCol++) {
		for (int row = 0; row < TILEBLOCKSIZEY; row++) {
			for (int col = 0; col < TILEBLOCKSIZEX; col++)
			{
				auto obj = m_arrTiles[0][blockCol][row][col];
				if (!obj) continue;
				auto tile = obj->GetScript<CTile>();
				if (tile->GetTileType() == TileType::Door)
				{
					return tile->Transform()->GetRelativePos();
				}
			}
		}
	}

	return Vec3();
}

void CTileMgr::Init()
{
	for (int blockrow = 0; blockrow < STAGETILEROW; blockrow++) {
		for (int blockcol = 0; blockcol < STAGETILECOL; blockcol++) {
			for (int row = 0; row < TILEBLOCKSIZEY; row++) {
				for (int col = 0; col < TILEBLOCKSIZEX; col++) {
					m_arrTiles[blockrow][blockcol][row][col] = nullptr;
				}
			}
		}
	}

	m_LayerCheck = 0;
}

void CTileMgr::SetTile(CGameObject* tile, int _blockRow, int _blockCol, int _tileRow, int _tileCol)
{
	m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol] = tile;
}

CTile* CTileMgr::GetTile(Vec2 _idx)
{
	int blockRow = (int)_idx.y / TILEBLOCKSIZEY;
	int blockCol = (int)_idx.x / TILEBLOCKSIZEX;
	int tileRow = (int)_idx.y % TILEBLOCKSIZEY;
	int tileCol = (int)_idx.x % TILEBLOCKSIZEX;
	if (m_arrTiles[blockRow][blockCol][tileRow][tileCol] != nullptr) {
		return m_arrTiles[blockRow][blockCol][tileRow][tileCol]->GetScript<CTile>();
	}
	else {
		return nullptr;
	}
	
}

CTile* CTileMgr::GetTile(int _blockRow, int _blockCol, int _tileRow, int _tileCol)
{
	if (_tileRow >= TILEBLOCKSIZEY) {
		_blockRow += _tileRow / TILEBLOCKSIZEY;
		_tileRow = _tileRow % TILEBLOCKSIZEY;
	}
	if (_tileCol >= TILEBLOCKSIZEX) {
		_blockCol += _tileCol / TILEBLOCKSIZEX;
		_tileCol = _tileCol % TILEBLOCKSIZEX;
	}
	if (m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol]) {
		return m_arrTiles[_blockRow][_blockCol][_tileRow][_tileCol]->GetScript<CTile>();
	}
	return nullptr;
}

CCollider2D* CTileMgr::GetTileCollider(Vec2 _idx)
{
	int blockRow = (int)_idx.y / TILEBLOCKSIZEY;
	int blockCol = (int)_idx.x / TILEBLOCKSIZEX;
	int tileRow = (int)_idx.y % TILEBLOCKSIZEY;
	int tileCol = (int)_idx.x % TILEBLOCKSIZEX;

	if (m_arrTiles[blockRow][blockCol][tileRow][tileCol]) {
		return m_arrTiles[blockRow][blockCol][tileRow][tileCol]->Collider2D();
	}
	return nullptr;
}

Vec2 CTileMgr::PosToIdx(Vec3 _vPos)
{
	return Vec2((int)_vPos.x / TileScaleX, (int)-(_vPos.y / TileScaleY));
}

Vec3 CTileMgr::IdxToPos(Vec2 _Idx)
{
	return Vec3((0.5f + _Idx.x) * TileScaleX, -(0.5f + _Idx.y) * TileScaleY, 0.f);
}

Vec3 CTileMgr::IdxToPos(int _BlockRow, int _BlockCol, int _TileRow, int _TileCol)
{
	return IdxToPos(Vec2(_BlockCol * TILEBLOCKSIZEX + _TileCol, _BlockRow * TILEBLOCKSIZEY + _TileRow));
}

void CTileMgr::tick()
{
	for (UINT layer = 0; layer < LAYER_MAX; layer++)
	{
		if (m_LayerCheck & (1 << layer)) {
			CollisionWithTile(layer);
		}
	}


}

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>

void CTileMgr::CollisionWithTile(int _layer)
{
	auto level = CLevelMgr::GetInst()->GetCurrentLevel();
	auto layer = level->GetLayer(_layer);
	const vector<CGameObject*>& objects = layer->GetLayerObjects();

	for (int i = 0; i < objects.size(); i++) {
		Vec2 Idx = PosToIdx(objects[i]->Transform()->GetWorldPos());

		int searchSize = 2;
		for (int row = -searchSize; row < searchSize; row++) {
			for (int col = -searchSize; col < searchSize; col++)
			{
				int nrow = row + (int)Idx.y;
				int ncol = col + (int)Idx.x;
				if (0 <= nrow && nrow < TILEBLOCKSIZEY * STAGETILEROW && 0 <= ncol && ncol < TILEBLOCKSIZEX * STAGETILECOL) {
					auto left = objects[i]->Collider2D();
					auto right = GetTileCollider(Vec2(ncol, nrow));
					if (!left || (left->GetOwner() && left->GetOwner()->IsDead())) continue;
					if (!right || (right->GetOwner() && right->GetOwner()->IsDead())) continue;

					TileCollisionID ID = {};
					ID.LeftID = left->GetID();
					ID.RightID = right->GetID();

					// 이전 프레임 충돌 확인
					map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
					if (iter == m_mapPrevInfo.end())
					{
						m_mapPrevInfo.insert(make_pair(ID.id, false));
						iter = m_mapPrevInfo.find(ID.id);
					}

					bool bDead = objects[i]->IsDead();

					// 지금 겹쳐있다.
					if (CheckCollision(left, right))
					{
						// 이전에도 겹쳐있었다.
						if (iter->second)
						{
							if (bDead)
							{
								left->EndOverlap(right);
								right->EndOverlap(left);
							}
							else
							{
								left->Overlap(right);
								right->Overlap(left);
							}
						}

						// 이전에 충돌한 적이 없다.
						else
						{
							// 둘중 하나라도 Dead 상태면, 충돌을 없었던 것으로 한다.
							if (!bDead)
							{
								left->BeginOverlap(right);
								right->BeginOverlap(left);
								iter->second = true;
							}
						}
					}

					// 지금 떨어져 있다.
					else
					{
						// 이전에는 겹쳐있었다.
						if (iter->second)
						{
							left->EndOverlap(right);
							right->EndOverlap(left);
							iter->second = false;
						}
					}
				}
			}
		}
	}
}

bool CTileMgr::CheckCollision(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	if (!_pLeft->IsActivate() || !_pRight->IsActivate()) {
		return false;
	}

	const Matrix& matLeft = _pLeft->GetColliderWorldMat();
	const Matrix& matRight = _pRight->GetColliderWorldMat();

	if (_pLeft->GetType() == COLLIDER2D_TYPE::CIRCLE || _pRight->GetType() == COLLIDER2D_TYPE::CIRCLE) {
		if (_pLeft->GetType() == COLLIDER2D_TYPE::RECT) {
			auto temp = _pRight;
			_pRight = _pLeft;
			_pLeft = temp;
		}
		float minScale = min(_pRight->GetOffsetScale().x, _pRight->GetOffsetScale().y);
		Vec3 vRightPos = matRight.Pos();
		Vec3 vLeftPos = matLeft.Pos();

		vRightPos.z = 0;
		vLeftPos.z = 0;

		float distance = Vec3::Distance(vLeftPos, vRightPos);

		if (distance < _pLeft->GetRadius() + minScale) {
			return true;
		}
		else {
			return false;
		}
	}
	// Rect Local
	// 0 -- 1
	// |    |
	// 3 -- 2
	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, -0.5f, 0.f)
							  , Vec3(-0.5f, -0.5f, 0.f) };

	Vec3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrRect[1], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], matRight) - XMVector3TransformCoord(arrRect[0], matRight);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matRight) - XMVector3TransformCoord(arrRect[0], matRight);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft);

	// i 번째 투영축으로 4개의 표면벡터를 투영시킨다.
	for (int i = 0; i < 4; ++i)
	{
		// i 번째 표면백터를 투영축으로 삼는다
		Vec3 vProj = arrProj[i];

		// 단위벡터로 만들어서 내적할 경우 투영된 길이를 구할 수 있게 한다.
		vProj.Normalize();

		// 투영된 길이를 누적시킬 변수
		float ProjAcc = 0.f;

		// 반복문 돌면서 4개의 표면벡터를 지정된 투영축으로 투영시켜서 길이를 누적받는다.
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// 투영된 길이의 절반씩 합친 길이가 필요하기 때문에 전체 합친길이를 2 로 나눈다
		ProjAcc /= 2.f;

		// 두 충돌체의 중심을 이은 벡터도 투영시킨다.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// 중심을 이은 벡터를 투영시킨 길이가, 표면을 투영시킨 길이의 절반보다 크다면 
		// 둘을 분리시킬 수 있다.
		if (ProjAcc < fCenterDist)
		{
			return false;
		}
	}

	// 4번의 테스트동안 분리할 수 없었다.
	return true;
}
#include "pch.h"
#include "CCollider2D.h"

#include "CRenderMgr.h"

#include "CTransform.h"
#include "CScript.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_CollisionCount(0)
	, m_vOffsetScale(1, 1, 1)
	, m_bAbsolute(false)
	, m_Type(COLLIDER2D_TYPE::RECT)
	, m_bActive(true)
	, m_fRadius(1.f)
{
}

CCollider2D::CCollider2D(const CCollider2D& _OriginCollider2D)
	: CComponent(_OriginCollider2D)
	, m_vOffsetPos(_OriginCollider2D.m_vOffsetPos)
	, m_vOffsetScale(_OriginCollider2D.m_vOffsetScale)
	, m_CollisionCount(0)
	, m_bAbsolute(_OriginCollider2D.m_bAbsolute)
	, m_Type(_OriginCollider2D.m_Type)
	, m_bActive(true)
	, m_fRadius(1.f)
{
}

CCollider2D::~CCollider2D()
{
}

Vec2 CCollider2D::GetFinalScale()
{
	Vec3 vScale = m_vOffsetScale;
	if (!m_bAbsolute) {
		vScale = Transform()->GetWorldScale()* m_vOffsetScale;
	}
	return Vec2(vScale.x, vScale.y);
}

Vec2 CCollider2D::GetRelativePos()
{
	Vec3 ownerScale = Transform()->GetRelativeScale();
	return Vec2(ownerScale.x * m_vOffsetPos.x, ownerScale.y * m_vOffsetPos.y);
}

Vec2 CCollider2D::GetRelativeScale()
{
	Vec3 ownerScale = Transform()->GetRelativeScale();
	return Vec2(ownerScale.x * m_vOffsetScale.x, ownerScale.y * m_vOffsetScale.y);
}

void CCollider2D::finaltick()
{
	if (!m_bActive) return;

	// 최종 위치값을 계산
	Vec3 vObjPos = Transform()->GetRelativePos();
	m_PrevFinalPos = m_FinalPos;
	m_FinalPos = vObjPos + Vec3(GetRelativePos().x, GetRelativePos().y, 0);

	// 충돌체의 로컬 행렬 계산
	m_matColWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matColWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	// 충돌체에 적용시킬 GameObject 의 월드행렬
	const Matrix& matObjWorld = Transform()->GetWorldMat();

	// GameObject 의 Scale 에 영향을 받지 않으려는 경우
	if (m_bAbsolute)
	{
		Vec3 vWorldScale = Transform()->GetWorldScale();
		Matrix matScaleInv = XMMatrixScaling(vWorldScale.x, vWorldScale.y, vWorldScale.z);
		matScaleInv = XMMatrixInverse(nullptr, matScaleInv);

		// Object 의 Scale 의 역행렬을 사이에 배치해서 무효화 시킴
		m_matColWorld = m_matColWorld * matScaleInv *  matObjWorld;
	}
	else
	{
		m_matColWorld *= matObjWorld;
	}	

	// 충돌중이면 Red, 충돌하고 있지 않으면 Green
	if (CRenderMgr::GetInst()->IsDebugPosition() == false)
		return;
	if (m_Type == COLLIDER2D_TYPE::RECT) {
		if (0 == m_CollisionCount)
		{
			GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f), false);
		}
		else
		{
			GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f), false);
		}
	}
	else {
		if (0 == m_CollisionCount)
		{
			GamePlayStatic::DrawDebugCircle(m_matColWorld.Pos(), m_fRadius, Vec3(0.f, 1.f, 0.f), false);
		}
		else
		{
			GamePlayStatic::DrawDebugCircle(m_matColWorld.Pos(), m_fRadius, Vec3(1.f, 0.f, 0.f), false);
		}
	}

	
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	++m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->Overlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	--m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::SaveToFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
	fwrite(&m_Type, sizeof(UINT), 1, _File);	
}

void CCollider2D::SaveToFile(ofstream& fout)
{
	fout << m_vOffsetPos << endl;
	fout << m_vOffsetScale << endl;
	fout << m_bAbsolute << endl;
	fout << (int)m_Type << endl;
}

void CCollider2D::LoadFromFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
	fread(&m_Type, sizeof(UINT), 1, _File);
}

void CCollider2D::LoadFromFile(ifstream& fin)
{
	int num;
	fin >> m_vOffsetPos >> m_vOffsetScale >> m_bAbsolute >> num;
	m_Type = (COLLIDER2D_TYPE)num;
}

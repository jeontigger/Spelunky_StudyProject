#include "pch.h"
#include "CMovement.h"

CMovement::CMovement()
	:CScript((UINT)SCRIPT_TYPE::MOVEMENT)
	, m_vGravityForce(Vec3(0.f, -981.f * 3.f, 0.f))
	, m_fMass(1.f)
	, m_fInitSpeed(0.f)
	, m_fMaxSpeed_Ground(100.f)
	, m_fMaxSpeed_InAir(1000.f)
	, m_fFrictionScale(0.f)
	, m_bUseGravity(true)
	, m_bGround(false)
{
}

CMovement::~CMovement()
{
}


void CMovement::begin()
{
}

void CMovement::finaltick()
{
	// ------------------------------
	// 0. ���ӵ� ���
	// ------------------------------
	m_vAccel = m_vForce / m_fMass;

	if (m_bUseGravity && !m_bGround)
	{
		m_vAccel += m_vGravityForce;
	}
	else if (m_bUseGravity && m_bGround)
	{
		m_vAccel.y = 0.f; // @TODO ���ӵ��� �״�� �ΰ�, ���� ���� ���� ����
	}

	// ------------------------------
	// 1. �ӵ� ���
	// ------------------------------
	// case: ���� �ֱ� �����ϴ� ��� �ʱ���� ����
	//if (m_vVelocity.Length() < 0.1f && m_vAccel != Vec3())
	//{
	//	Vec3 vAccelDir = m_vAccel;
	//	vAccelDir.Normalize();
	//	m_vVelocity = vAccelDir * m_fInitSpeed;
	//}
	//else
	//{
	//	
	//}

	m_vVelocity += m_vAccel * DT;

	// �ִ� �ӵ� ����
	//if (m_bGround && fabs(m_vVelocity.Length() > m_fMaxSpeed_Ground))
	//{
	//	m_vVelocity = m_vVelocity.Normalize() * m_fMaxSpeed_Ground;
	//}

	if (not m_bGround && (fabs(m_vVelocity.y) > m_fMaxSpeed_InAir))
	{
		m_vVelocity.y = (m_vVelocity.y / fabs(m_vVelocity.y)) * m_fMaxSpeed_InAir;
	}

	// ------------------------------
	// ������ ���
	// ------------------------------
	// - ��ü�� ����ǰ� �ִ� ���� ������ �������� ����
	if (m_vForce == Vec3() && m_vVelocity.x != 0.f && m_bGround)
	{
		// ������ ũ��
		float fFriction = -m_vVelocity.x / fabs(m_vVelocity.x);
		fFriction *= m_fFrictionScale;

		// ���� ������ ũ��
		float fFrictionAccel = (fFriction / m_fMass) * DT;
		if (fabs(m_vVelocity.x) < fabs(fFrictionAccel))
		{
			m_vVelocity.x = 0.f;
		}
		else
			m_vVelocity.x += fFrictionAccel;
	}

	// ------------------------------
	// ��ġ ���
	// ------------------------------
	Vec3 vObjPos = GetOwner()->Transform()->GetRelativePos();
	vObjPos += m_vVelocity * DT;
	GetOwner()->Transform()->SetRelativePos(vObjPos);

	// ------------------------------
	// �� ����
	// ------------------------------
	// - �̵��ϰ��� �ϴ� �� ���� ���� ���ϴ� ���
	m_vForce = Vec3();
}

void CMovement::CalDir()
{
	m_Dir = 0;

	Vec3 PrevPos = Transform()->GetPrevPos();
	Vec3 CurPos = Transform()->GetCurPos();

	Vec3 Dir = GetVelocity();

	if (Dir.x > 0)
	{
		m_Dir |= (UINT)MoveDir::RIGHT;
	}

	if (Dir.x < 0)
	{
		m_Dir |= (UINT)MoveDir::LEFT;
	}

	if (Dir.y > 0)
	{
		m_Dir |= (UINT)MoveDir::UP;
	}

	if (Dir.y < 0)
	{
		m_Dir |= (UINT)MoveDir::DOWN;
	}
}
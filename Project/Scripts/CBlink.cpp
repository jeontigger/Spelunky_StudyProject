#include "pch.h"
#include "CBlink.h"

CBlink::CBlink()
	:CScript((UINT)SCRIPT_TYPE::BLINK)
	, m_fOnTime(1.f)
	, m_fOffTime(1.f)
{
}

CBlink::~CBlink()
{
}

void CBlink::begin()
{
	m_fOnTimer = m_fOnTime;
	m_fOffTimer = m_fOffTime;
}

void CBlink::tick()
{
	if (Collider2D()->IsActivate()) {
		m_fOnTimer -= DT;

		if (m_fOnTimer <= 0) {
			m_fOffTimer += m_fOffTime;
			Collider2D()->Activate(false);
		}
	}
	else {
		m_fOffTimer -= DT;

		if (m_fOffTimer <= 0) {
			m_fOnTimer += m_fOnTime;
			Collider2D()->Activate(true);
		}
	}
}

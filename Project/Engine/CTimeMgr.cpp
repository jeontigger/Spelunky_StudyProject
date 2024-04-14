#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CFontMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Time(0.f)
	, m_bLock(false)
	, m_szText{}
{	

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// 초당 빈도
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_EngineDeltaTime = m_DeltaTime = double(m_CurCount.QuadPart - m_PrevCount.QuadPart) / double(m_Frequency.QuadPart);

	if (m_bLock)
	{
		m_DeltaTime = 0.f;
	}

	m_PrevCount = m_CurCount;

	// DT 보정
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1. / 60.);

	// 시간 누적 ==> 1초마다 if 구문 실행
	m_Time += m_EngineDeltaTime;
	m_szText[50] = {};
	if (1.f <= m_Time)
	{		
		swprintf_s(m_szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		m_iCall = 0;
		m_Time = 0.f;

		// 폰트 출력
		Font data = {};
		data._Color = FONT_RGBA(255, 30, 30, 255);
		data._fFontSize = 16;
		data._fPosX = 10.f;
		data._fPosY = 30.f;
		//CFontMgr::GetInst()->DrawFont(m_szText, data, 1.f);
	}

	++m_iCall;	
	g_global.g_time += (float)m_DeltaTime;	
	g_global.g_dt = (float)m_DeltaTime;
}

void CTimeMgr::render()
{

}
#include "pch.h"
#include "CFontMgr.h"

#include "CDevice.h"
#include "CTimeMgr.h"

CFontMgr::CFontMgr()
	: m_pFW1Factory(nullptr)
	, m_pFontWrapper(nullptr)
{
}

CFontMgr::~CFontMgr()
{
	if (nullptr != m_pFW1Factory)
		m_pFW1Factory->Release();

	if (nullptr != m_pFontWrapper)
		m_pFontWrapper->Release();
}

void CFontMgr::render()
{
	for (auto iter = m_listFont.begin(); iter != m_listFont.end();) {
		FontData& data = *iter;
		data._acc += DT_ENGINE;

		m_pFontWrapper->DrawString(
			CONTEXT,
			data._str, // String
			data._font._fFontSize,// Font size
			data._font._fPosX,// X position
			data._font._fPosY,// Y position
			data._font._Color,// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);

		if (data._acc > data._time) {
			iter = m_listFont.erase(iter);
		}
		else {
			++iter;
		}
	}
}

void CFontMgr::init()
{
	if (FAILED(FW1CreateFactory(FW1_VERSION, &m_pFW1Factory)))
	{
		assert(NULL);
	}
	
	if (FAILED(m_pFW1Factory->CreateFontWrapper(DEVICE, L"³ª´®½ºÄù¾î ³×¿À Regular", &m_pFontWrapper)))
	{
		assert(NULL);
	}
}

void CFontMgr::DrawFont(const wchar_t* _str, const Font& _data, float _time)
{
	m_listFont.push_back({ _str, _data, 0.f, _time });
}
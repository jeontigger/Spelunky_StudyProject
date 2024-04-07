#include "pch.h"
#include "CRandomMgr.h"

#include <random>
#include <Engine/CFontMgr.h>

CRandomMgr::CRandomMgr()
{
}

CRandomMgr::~CRandomMgr()
{
}

void CRandomMgr::GenNewSeed(UINT32 _seed)
{
    // ���� ���� ���� �ʱ�ȭ�� ���� �õ� ����
    m_seed = _seed;
    std::mt19937 gen(m_seed); // Mersenne Twister ���� ���� ���� �ʱ�ȭ
    m_GenEngine = gen;
    std::uniform_int_distribution<> dis(0, RandomAccuracy - 1);
    m_DistGenerator = dis;


    m_strPrint = L"Seed == " + std::to_wstring(m_seed);
    Font data = {};
    data._fPosX = 1250.f;
    data._fPosY = 30.f;
    data._fFontSize = 32;
    data._Color = FONT_RGBA(255, 30, 30, 255);
    CFontMgr::GetInst()->DrawFont(m_strPrint.c_str(), data, 1.f);
}

void CRandomMgr::SetSeed(UINT32 _seed)
{
    GenNewSeed(_seed);
}

void CRandomMgr::init()
{
    std::random_device rd; // �ϵ���� ���� �����⸦ ����Ͽ� �õ� ����
    GenNewSeed(rd());
}

int CRandomMgr::GetRandom(int _bound)
{
    return  m_DistGenerator(m_GenEngine)%_bound;
}

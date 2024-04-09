#pragma once
#include <Engine/CScript.h>
class CAnimationLoop :
    public CScript
{
private:
    int m_iLoopCount;
    wstring m_strAnimName;

    list<wstring> m_listWait;

public:
    void Set(const wstring& _animName, int _loopCnt);
    void Set(const std::initializer_list<wstring>& strings) {
        for (const auto& str : strings) {
            // wcout를 사용하여 std::wstring 출력
            m_listWait.push_back(str);
        }
    }

public:
    static CGameObject* Instantiate();
    
public:
    virtual void begin() override;
    virtual void tick() override;

public:
    CLONE(CAnimationLoop);
    CAnimationLoop();
    ~CAnimationLoop();

private:
    void PlayFront();
};


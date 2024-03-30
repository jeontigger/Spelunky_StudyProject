#pragma once
#include "ComponentUI.h"
class Animator2DUI :
    public ComponentUI
{
private:
    class CAnimator2D* m_target;
    vector<string> m_vecAnimNames;

    int m_iAnimCnt;

public:
    virtual void render_update() override;
    virtual void Activate() override;

public:
    Animator2DUI();
    ~Animator2DUI();

private:
    // 현재 애니메이션 출력
    void CurAnim();
    // 애니메이션 목록 출력
    void AnimList();
    // 애니메이션 추가
    void AddAnim();

public:
    void LoadAnims();

};


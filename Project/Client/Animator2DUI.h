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
    // ���� �ִϸ��̼� ���
    void CurAnim();
    // �ִϸ��̼� ��� ���
    void AnimList();
    // �ִϸ��̼� �߰�
    void AddAnim();

public:
    void LoadAnims();

};


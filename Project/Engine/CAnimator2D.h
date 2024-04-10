#pragma once
#include "CComponent.h"

#include "CTexture.h"
#include "CAnim.h"

class CAnim;


class CAnimator2D :
    public CComponent
{
private:
    map<wstring, CAnim*>    m_mapAnim;
    CAnim*                  m_CurAnim;
    bool                    m_bRepeat;

public:
    virtual void finaltick() override;

    void UpdateData();
    static void Clear();

    // _LeftTop, _SliceSize, _Offset : Pixel Unit
    void Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS);
    void AddAnim(const wstring& _strKey, Ptr<CTexture> _AltasTex, const vector<tAnimFrm>& frms);
    void AddAnim(CAnim* anim);

    CAnim* GetCurAnim() { return m_CurAnim; }
    CAnim* FindAnim(const wstring& _strAnimName);
    CAnim* FindAnim(const string& _strAnimName);
    void Play(const wstring& _strAnimName, bool _bRepeat = true);
    void Stop();

    virtual void SaveToFile(FILE* _File) override;
    virtual void SaveToFile(ofstream& fout) override;
    virtual void LoadFromFile(FILE* _File) override;
    virtual void LoadFromFile(ifstream& fin) override;
    CLONE(CAnimator2D);
public:
    CAnimator2D();
    CAnimator2D(const CAnimator2D& _OriginAnimator);
    ~CAnimator2D();

    friend class Animator2DUI;

public:
    static float GetAnimDuration(CAnim* anim);
};


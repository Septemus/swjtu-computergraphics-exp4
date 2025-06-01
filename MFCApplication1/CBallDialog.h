#pragma once
#include <afxwin.h>
#include "resource.h"

class CBallDialog :
    public CDialog
{
private:
    int radius=0;
    int slice=0;
    int stack=0;
    bool useSkeleton = false;
public:
    enum { IDD = IDD_BALL_DIALOG };

    CBallDialog();
    ~CBallDialog();
    DECLARE_MESSAGE_MAP()
        afx_msg void OnBnClickedOk();
        afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
        afx_msg void OnBnClickedSkeleton();
        afx_msg void OnBnClickedSurface();
};


#pragma once
#include <afxwin.h>
#include "resource.h"
class CDialogButton2 :
    public CDialog
{
public:
    enum { IDD = IDD_DIALOG2 };
    CDialogButton2();
    ~CDialogButton2();
    DECLARE_MESSAGE_MAP()
        afx_msg void OnBnClickedOk();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


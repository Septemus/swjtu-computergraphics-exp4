#pragma once
#include <afxwin.h>
#include "resource.h"

class CMFCApplication1Doc;
class CDialogButton1 :
    public CDialog
{
public:
    enum { IDD = IDD_DIALOG1 };
    CDialogButton1();
    ~CDialogButton1();
    DECLARE_MESSAGE_MAP()
//        afx_msg void OnBnClickedRadio2();
afx_msg void OnBnClickedOk();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


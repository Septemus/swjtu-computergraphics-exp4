#include "pch.h"
#include "CDialogButton2.h"
#include "MFCApplication1Doc.h"
#include "framework.h"
#include "MainFrm.h"
CDialogButton2::CDialogButton2() :CDialog(CDialogButton2::IDD) {

}

CDialogButton2::~CDialogButton2() {

}BEGIN_MESSAGE_MAP(CDialogButton2, CDialog)
ON_BN_CLICKED(IDOK, &CDialogButton2::OnBnClickedOk)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


void CDialogButton2::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCApplication1Doc* pDoc = (CMFCApplication1Doc*)pMain->GetActiveDocument();
	pDoc->m_str = CString(_T("button2"));
	pDoc->target = new Cordinate<int>(GetDlgItemInt(IDC_EDIT1), GetDlgItemInt(IDC_EDIT2));
	pDoc->radius = GetDlgItemInt(IDC_EDIT3);
	pDoc->angle = GetDlgItemInt(IDC_EDIT4);
	CString algo;
	int selectedId = GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO2);
	switch (selectedId) {
		case IDC_RADIO1: {
			algo = "midpoint";
			break;
		}
		case IDC_RADIO2: {
			algo = "bresenham";
			break;
		}
	}
	pDoc->algo = algo;
	pDoc->UpdateAllViews(NULL);
	CDialog::OnOK();
}



HBRUSH CDialogButton2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_RADIO1:
		return CreateSolidBrush(RGB(255, 0, 0));
		break;
	case IDC_RADIO2:
		return CreateSolidBrush(RGB(0, 255, 0));
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

#include "pch.h"
#include "CDialogButton1.h"
#include "MFCApplication1Doc.h"
#include "framework.h"
#include "MainFrm.h"
CDialogButton1::CDialogButton1() :CDialog(CDialogButton1::IDD) {

}

CDialogButton1::~CDialogButton1() {

}BEGIN_MESSAGE_MAP(CDialogButton1, CDialog)
//ON_BN_CLICKED(IDC_RADIO2, &CDialogButton1::OnBnClickedRadio2)
ON_BN_CLICKED(IDOK, &CDialogButton1::OnBnClickedOk)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


//void CDialogButton1::OnBnClickedRadio2()
//{
	// TODO: 在此添加控件通知处理程序代码
//}


void CDialogButton1::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCApplication1Doc* pDoc=(CMFCApplication1Doc*)pMain->GetActiveDocument();
	CString algo;
	int selectedId=GetCheckedRadioButton(IDC_RADIO1, IDC_RADIO3);
	switch (selectedId) {
		case IDC_RADIO1: {
			algo = "dda";
			break;
		}
		case IDC_RADIO2: {
			algo = "midpoint";
			break;
		}
		case IDC_RADIO3: {
			algo = "bresenham";
			break;
		}
	}
	if (!pDoc) return;
	pDoc->m_str = CString(_T("button1"));
	pDoc->target = new Cordinate<int>(GetDlgItemInt(IDC_EDIT3), GetDlgItemInt(IDC_EDIT2));
	pDoc->algo = algo;
	pDoc->numOfEdges = GetDlgItemInt(IDC_EDIT1);
	pDoc->UpdateAllViews(NULL);
	CDialog::OnOK();
}


HBRUSH CDialogButton1::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	case IDC_RADIO3:
		return CreateSolidBrush(RGB(0, 199, 199));
		break;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

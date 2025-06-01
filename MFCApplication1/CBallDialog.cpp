#include "pch.h"
#include "CBallDialog.h"
CBallDialog::CBallDialog() :CDialog(CBallDialog::IDD) {

}

CBallDialog::~CBallDialog() {

}BEGIN_MESSAGE_MAP(CBallDialog, CDialog)
ON_BN_CLICKED(IDOK, &CBallDialog::OnBnClickedOk)
ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CBallDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
void CBallDialog::OnHScroll(UINT nSHCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* ACSliderCtrl = (CSliderCtrl*)pScrollBar;
	int nID = ACSliderCtrl->GetDlgCtrlID();
	int NewPos = ((CSliderCtrl*)pScrollBar)->GetPos();
	TRACE("slider %d new position: %d \n",nID,NewPos);
	switch (nID) {
	case IDC_RADIUS: {
		radius = NewPos * 5;
		break;
	}
	case IDC_SLICE: {
		slice = NewPos / 2;
		break;
	}
	case IDC_STACK: {
		stack = NewPos / 2;
		break;
	}
	}
	TRACE("state after sliding:\t radius:%d \t slice:%d \t stack:%d \n", radius, slice, stack);
	CString t;
	t.Format(_T("%d"), radius);
	CWnd* radiusValue = GetDlgItem(IDC_RADIUS_VALUE);
	radiusValue->SetWindowTextW(t);
	t.Format(_T("%d"), slice);
	CWnd* sliceValue = GetDlgItem(IDC_SLICE_VALUE);
	sliceValue->SetWindowTextW(t);
	t.Format(_T("%d"), stack);
	CWnd* stackValue = GetDlgItem(IDC_STACK_VALUE);
	stackValue->SetWindowTextW(t);
	CDialog::OnHScroll(nSHCode, nPos, pScrollBar);
}
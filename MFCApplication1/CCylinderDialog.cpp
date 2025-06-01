#include "pch.h"
#include "CCylinderDialog.h"
#include "MainFrm.h"
#include "MFCApplication1Doc.h"
CCylinderDialog::CCylinderDialog() :CDialog(CCylinderDialog::IDD) {

}

CCylinderDialog::~CCylinderDialog() {

}BEGIN_MESSAGE_MAP(CCylinderDialog, CDialog)
ON_BN_CLICKED(IDOK, &CCylinderDialog::OnBnClickedOk)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_SKELETON, &CCylinderDialog::OnBnClickedSkeleton)
ON_BN_CLICKED(IDC_SURFACE, &CCylinderDialog::OnBnClickedSurface)
END_MESSAGE_MAP()


void CCylinderDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCApplication1Doc* pDoc = (CMFCApplication1Doc*)pMain->GetActiveDocument();
	CEdit* xedit = (CEdit*)GetDlgItem(IDC_X_AXIS);
	CEdit* yedit = (CEdit*)GetDlgItem(IDC_Y_AXIS);
	CString tmpx, tmpy;
	xedit->GetWindowTextW(tmpx);
	yedit->GetWindowTextW(tmpy);
	pDoc->drawCylinder(upRadius,downRadius,h, slice, stack, useSkeleton, _ttoi(tmpx), _ttoi(tmpy));
	CDialog::OnOK();
}
void CCylinderDialog::OnHScroll(UINT nSHCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* ACSliderCtrl = (CSliderCtrl*)pScrollBar;
	int nID = ACSliderCtrl->GetDlgCtrlID();
	int NewPos = ((CSliderCtrl*)pScrollBar)->GetPos();
	TRACE("slider %d new position: %d \n", nID, NewPos);
	switch (nID) {
	case IDC_UP_RADIUS: {
		upRadius = NewPos * 5;
		break;
	}
	case IDC_DOWN_RADIUS: {
		downRadius = NewPos * 5;
		break;
	}
	case IDC_HEIGHT: {
		h = NewPos * 3;
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
	TRACE("state after sliding:\t up-radius:%d \t down-radius:%d \t height:%d \t slice:%d \t stack:%d \n", upRadius,downRadius,h, slice, stack);
	CString t;
	t.Format(_T("%d"), upRadius);
	CWnd* upRadiusValue = GetDlgItem(IDC_UP_RADIUS_VALUE);
	upRadiusValue->SetWindowTextW(t);

	t.Format(_T("%d"), downRadius);
	CWnd* downRadiusValue = GetDlgItem(IDC_DOWN_RADIUS_VALUE);
	downRadiusValue->SetWindowTextW(t);

	t.Format(_T("%d"), h);
	CWnd* heightValue = GetDlgItem(IDC_HEIGHT_VALUE);
	heightValue->SetWindowTextW(t);

	t.Format(_T("%d"), slice);
	CWnd* sliceValue = GetDlgItem(IDC_SLICE_VALUE);
	sliceValue->SetWindowTextW(t);

	t.Format(_T("%d"), stack);
	CWnd* stackValue = GetDlgItem(IDC_STACK_VALUE);
	stackValue->SetWindowTextW(t);

	CDialog::OnHScroll(nSHCode, nPos, pScrollBar);
}

void CCylinderDialog::OnBnClickedSkeleton()
{
	// TODO: 在此添加控件通知处理程序代码
	useSkeleton = true;
}


void CCylinderDialog::OnBnClickedSurface()
{
	// TODO: 在此添加控件通知处理程序代码
	useSkeleton = false;
}

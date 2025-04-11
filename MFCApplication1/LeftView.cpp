// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// LeftView.cpp: CLeftView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1View.h"
#include "MFCApplication1Doc.h"
#include "LeftView.h"
#include "CDialogButton1.h"
#include "CDialogButton2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	ON_WM_CREATE()
	ON_BN_CLICKED(BUTTON_1,onButton1Clicked)
	ON_BN_CLICKED(BUTTON_2,onButton2Clicked)
END_MESSAGE_MAP()


// CLeftView 构造/析构

CLeftView::CLeftView()
{
	// TODO: 在此处添加构造代码
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。
}


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG
CMFCApplication1Doc* CLeftView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}


afx_msg void CLeftView::onButton1Clicked()
{
	CDialogButton1 bt1Dialog;
	bt1Dialog.DoModal();
	return;
}

afx_msg void CLeftView::onButton2Clicked()
{
	CDialogButton2 bt2Dialog;
	bt2Dialog.DoModal();
	return;
}


// CLeftView 消息处理程序


int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Create the button
	button1.Create(_T("正多边形绘制"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 10, 200, 50), this, BUTTON_1);
	button2.Create(_T("圆绘制"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 50, 200, 90), this, BUTTON_2);
	return 0;
}

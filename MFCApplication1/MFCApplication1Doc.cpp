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

// MFCApplication1Doc.cpp: CMFCApplication1Doc 类的实现
//
//

#include "pch.h"
#include "framework.h"
#include "UIEventHandler.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif
#include "LeftView.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CCGRenderContext.h"
#include "UIEventHandler.h"
#include "CGDraw2DLineSeg.h"
#include "CGDraw2DLineLoop.h"
#include "CGDraw2DLineStrip.h"
#include "CGModel2DTransormMove.h"
#include "CGModel2DTransformRotate.h"
#include "CGModel2DTransformZoom.h"
#include "CGCube.h"
#include "TessellationHints.h"
#include "CBallDialog.h"
#include "CCylinderDialog.h"
#include "CGBall.h"
#include "CGCylinder.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
	ON_COMMAND(ID_DRAW2D_LINESEG, &CMFCApplication1Doc::OnDraw2dLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINESEG, &CMFCApplication1Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_LINE_LOOP, &CMFCApplication1Doc::OnDraw2dLineLoop)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINE_LOOP, &CMFCApplication1Doc::OnUpdateDraw2dLineLoop)
	ON_COMMAND(ID_DRAW2D_LINE_STRIP, &CMFCApplication1Doc::OnDraw2dLineStrip)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINE_STRIP, &CMFCApplication1Doc::OnUpdateDraw2dLineStrip)
	ON_COMMAND(ID_MOVE, &CMFCApplication1Doc::OnMove)
	ON_UPDATE_COMMAND_UI(ID_MOVE, &CMFCApplication1Doc::OnUpdateMove)
	ON_COMMAND(ID_ZOOM, &CMFCApplication1Doc::OnZoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, &CMFCApplication1Doc::OnUpdateZoom)
	ON_COMMAND(ID_MYROTATE, &CMFCApplication1Doc::OnRotation)
	ON_UPDATE_COMMAND_UI(ID_MYROTATE, &CMFCApplication1Doc::OnUpdateRotation)
	ON_COMMAND(ID_DRAW_BALL, &CMFCApplication1Doc::OnDrawBall)
	ON_UPDATE_COMMAND_UI(ID_DRAW_BALL, &CMFCApplication1Doc::OnUpdateDrawBall)
	ON_COMMAND(ID_CYLINDER, &CMFCApplication1Doc::OnCylinder)
	ON_UPDATE_COMMAND_UI(ID_CYLINDER, &CMFCApplication1Doc::OnUpdateCylinder)
END_MESSAGE_MAP()


// CMFCApplication1Doc 构造/析构

CMFCApplication1Doc::CMFCApplication1Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	//长方体（模型）
	auto c = std::make_shared<CGCube>();
	auto h = std::make_shared<TessellationHints>();
	c->setTessellationHints(h);
	c->setDisplayListEnabled(true);
	//右长方体实例节点
	auto t1 = std::make_shared<CGTransform>(); //实列组节点
	auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	auto color1 = std::make_shared<CGColor>(); //属性
	color1->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); //黄色
	e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
	t1->translate(100, 0, 0);
	t1->rotate(45, 1, 1, 1);
	t1->scale(100, 100, 100);
	e1->AddChild(c);
	t1->AddChild(e1);
	mScene->GetSceneData()->asGroup()->AddChild(t1);
	//左长方体节点
	auto t2 = std::make_shared<CGTransform>(); //实列组节点
	auto e2 = std::make_shared<CGGeode>(); //实列叶节点
	auto color2 = std::make_shared<CGColor>(); //属性
	color2->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //蓝色
	e2->gocRenderStateSet()->setRenderState(color2, -1); //设置节点属性
	auto p = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
	e2->gocRenderStateSet()->setRenderState(p, -1); //设置节点属性
	t2->translate(-100, 0, 0);
	t2->rotate(45, 1, 1, 1);
	t2->scale(100, 100, 100);
	e2->AddChild(c);
	t2->AddChild(e2);
	mScene->GetSceneData()->asGroup()->AddChild(t2);
}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	SetTitle(_T("图形学实验4"));
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMFCApplication1Doc 序列化

void CMFCApplication1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication1Doc 诊断

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication1Doc 命令


bool CMFCApplication1Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;
	return mScene->Render(pRC, pCamera);
}

bool CMFCApplication1Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mScene == nullptr)
		return false;
	if (mSelectedGroup) { //需要先选中一各组节点
		//模型加入实例节点后加入场景
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetLeftView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
	}
	return false;
}

void CMFCApplication1Doc::OnDraw2dLineseg()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Draw2DLineSeg);
}



void CMFCApplication1Doc::OnDraw2dLineLoop()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineLoop(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateDraw2dLineLoop(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Draw2DLineLoop);
}


void CMFCApplication1Doc::OnDraw2dLineStrip()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Draw2DLineStrip);
}
CLeftView* CMFCApplication1Doc::GetLeftView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CLeftView))) {
			CLeftView* view = dynamic_cast<CLeftView*>(pView);
			return view;
		}
	}
	return nullptr;
}
void CMFCApplication1Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;//
	CString str(_T("场景"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));
	InstToSceneTree(pTree, hInst, mScene->GetSceneData());
	pTree->Expand(hInst, TVE_EXPAND);
}
void CMFCApplication1Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);//
	if (node->asGeode()) {
		CString str(_T("Geode"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//叶子实例节点不再显示模型节点
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		CString str(_T("Group"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}
	}
}
void CMFCApplication1Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //不允许叶子节点上再
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}

void CMFCApplication1Doc::OnMove()
{
	// TODO: 在此添加命令处理程序代码
	if (!mSelectedItem) {
		AfxMessageBox(_T("请先选择添加节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGModel2DTransormMove(view->glfwWindow(),(CGGeode*)GetLeftView()->GetTreeCtrl().GetItemData(mSelectedItem) ) ); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateMove(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Model2DTransformMove);
}





void CMFCApplication1Doc::OnZoom()
{
	// TODO: 在此添加命令处理程序代码
	if (!mSelectedItem) {
		AfxMessageBox(_T("请先选择添加节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGModel2DTransformZoom(view->glfwWindow(), (CGGeode*)GetLeftView()->GetTreeCtrl().GetItemData(mSelectedItem))); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateZoom(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Model2DTransformZoom);
}


void CMFCApplication1Doc::OnRotation()
{
	// TODO: 在此添加命令处理程序代码
	if (!mSelectedItem) {
		AfxMessageBox(_T("请先选择添加节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGModel2DTransformRotate(view->glfwWindow(), (CGGeode*)GetLeftView()->GetTreeCtrl().GetItemData(mSelectedItem))); //创建绘制直线段的命令对象
	}
}


void CMFCApplication1Doc::OnUpdateRotation(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Model2DTransformRotate);
}


void CMFCApplication1Doc::OnDrawBall()
{
	// TODO: 在此添加命令处理程序代码
	CBallDialog ballDlg;
	ballDlg.DoModal();
}


void CMFCApplication1Doc::OnUpdateDrawBall(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	/*pCmdUI->SetCheck(dlg!=NULL);
	return;*/
}


void CMFCApplication1Doc::OnCylinder()
{
	// TODO: 在此添加命令处理程序代码
	CCylinderDialog cylinderDlg;
	cylinderDlg.DoModal();
}


void CMFCApplication1Doc::OnUpdateCylinder(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
void CMFCApplication1Doc::drawBall(int radius, int slice, int stack,bool useSkeleton,int xval=300,int yval=200) {
	//球体（模型）
	auto c = std::make_shared<CGBall>();
	auto h = std::make_shared<TessellationHints>();
	h->setTargetSlices(slice);
	h->setTargetStacks(stack);
	c->setTessellationHints(h);
	c->setDisplayListEnabled(true);
	//右长方体实例节点
	auto t1 = std::make_shared<CGTransform>(); //实列组节点
	auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	auto color1 = std::make_shared<CGColor>(); //属性
	color1->setValue(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); //绿色
	e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
	t1->translate(xval, yval, 0);
	t1->rotate(45, 1, 1, 1);
	t1->scale(radius, radius, radius);
	e1->AddChild(c);
	if (useSkeleton) {
		auto p = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
		e1->gocRenderStateSet()->setRenderState(p, -1); //设置节点属性
	}
	t1->AddChild(e1);
	mScene->GetSceneData()->asGroup()->AddChild(t1);
	CTreeCtrl& tree = GetLeftView()->GetTreeCtrl();
	HTREEITEM hRoot = tree.GetRootItem();
	InstToSceneTree(&tree, tree.GetChildItem(hRoot), t1.get());
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	view->Invalidate(); //客户区需要重绘
	view->UpdateWindow(); //客户区执行重绘
}

void CMFCApplication1Doc::drawCylinder(int upRadius,int downRadius,int height, int slice, int stack, bool useSkeleton, int xval = 300, int yval = 200) {
	//球体（模型）
	auto c = std::make_shared<CGCylinder>(upRadius,downRadius,height);
	auto h = std::make_shared<TessellationHints>();
	h->setTargetSlices(slice);
	h->setTargetStacks(stack);
	c->setTessellationHints(h);
	c->setDisplayListEnabled(true);
	//右长方体实例节点
	auto t1 = std::make_shared<CGTransform>(); //实列组节点
	auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	auto color1 = std::make_shared<CGColor>(); //属性
	color1->setValue(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); //红色
	e1->gocRenderStateSet()->setRenderState(color1, -1); //设置节点属性
	t1->translate(xval, yval, 0);
	t1->rotate(45, 1, 1, 1);
	e1->AddChild(c);
	if (useSkeleton) {
		auto p = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式
		e1->gocRenderStateSet()->setRenderState(p, -1); //设置节点属性
	}
	t1->AddChild(e1);
	mScene->GetSceneData()->asGroup()->AddChild(t1);
	CTreeCtrl& tree = GetLeftView()->GetTreeCtrl();
	HTREEITEM hRoot = tree.GetRootItem();
	InstToSceneTree(&tree, tree.GetChildItem(hRoot), t1.get());
	CMFCApplication1View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMFCApplication1View))) {
			view = dynamic_cast<CMFCApplication1View*>(pView);
			break;
		}
	}
	view->Invalidate(); //客户区需要重绘
	view->UpdateWindow(); //客户区执行重绘
}
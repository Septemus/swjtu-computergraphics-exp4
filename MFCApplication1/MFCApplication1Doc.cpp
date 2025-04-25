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

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CCGRenderContext.h"
#include "UIEventHandler.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
	ON_COMMAND(ID_DRAW2D_LINESEG, &CMFCApplication1Doc::OnDraw2dLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINESEG, &CMFCApplication1Doc::OnUpdateDraw2dLineseg)
END_MESSAGE_MAP()


// CMFCApplication1Doc 构造/析构

CMFCApplication1Doc::CMFCApplication1Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	mScene->SetMainCamera(std::make_shared<CGCamera>());
	auto e = std::make_shared<CGGeode>();
	auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	e->AddChild(line);
	auto g = std::make_shared<CGTransform>();
	g->AddChild(e);
	mScene->SetSceneData(g);

}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	SetTitle(_T("图形学实验2"));
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
	CGGroup* g = mScene->GetSceneData()->asGroup();
	if (g) {
		g->AddChild(r);
		return true;
	}
	return false;
}

void CMFCApplication1Doc::OnDraw2dLineseg()
{
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

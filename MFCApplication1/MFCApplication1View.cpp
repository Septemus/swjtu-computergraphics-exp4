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

// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Cordinate.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	ON_WM_STYLECHANGED()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码


}

CMFCApplication1View::~CMFCApplication1View()
{

	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

void CMFCApplication1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
}

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument()  // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序
void CMFCApplication1View::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: 添加代码以响应用户对窗口视图样式的更改
	CView::OnStyleChanged(nStyleType,lpStyleStruct);
}

bool CMFCApplication1View::InitGLFW()
{
	if (!glfwInit()) {
		AfxMessageBox(_T("GLFW初始化失败"));
		return false;
	}
	// 设置GLFW窗口无边框、透明（避免覆盖MFC控件）
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	// 设置OpenGL版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //如果使用OpenGL核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //如果使用OpenGL兼容模式
	// 创建隐藏的GLFW窗口
	m_glfwWindow = glfwCreateWindow(100, 100, "", NULL, NULL);
	if (!m_glfwWindow) {
		AfxMessageBox(_T("Failed to glfwCreateWindow"));
		glfwTerminate();
		return false;
	}
	// 获取GLFW窗口的HWND并设置为MFC视图的子窗口
	m_hWndGL = glfwGetWin32Window(m_glfwWindow);
	SetWindowLong(m_hWndGL, GWL_STYLE, WS_VISIBLE);
	::SetParent(m_hWndGL, GetSafeHwnd());
	::ShowWindow(m_hWndGL, SW_SHOW);
	// 初始化OpenGL上下文
	glfwMakeContextCurrent(m_glfwWindow);
#if defined(_USE_GLEW)
	glewInit();
#else
	//使用GLAD来加载OpenGL的函数地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		AfxMessageBox(_T("Failed to initialize GLAD"));
		return false;
	}
#endif
	// 设置视口
	CRect rect;
	GetClientRect(&rect);
	glViewport(0, 0, rect.Width(), rect.Height());
	m_bGLInitialized = true;
	return true;
}

void CMFCApplication1View::RenderScene(CString m_str)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	if (!m_bGLInitialized)
		return;
	glfwMakeContextCurrent(m_glfwWindow);
	glfwSwapBuffers(m_glfwWindow);
	//启用渲染环境
	//此处添加自定义OpenGL渲染代码...
	if (m_str.Compare(_T("button1"))==0) {
		
		drawEqualPolygon(pDoc->target, pDoc->numOfEdges, pDoc->algo);
	}
	else if(m_str.CompareNoCase(_T("button2"))==0) {
		glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
		if (pDoc->algo == _T("bresenham")) {
			color= glm::vec3(0.0f, 1.0f, 0.0f);
		}
		drawArc(pDoc->target, pDoc->radius, pDoc->angle,color,pDoc->algo);
	}
	glfwSwapBuffers(m_glfwWindow);
	pDoc->resizing = false;
}


int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: 在此添加您专用的创建代码
	if (!InitGLFW())
		return -1;
	return 0;
}


void CMFCApplication1View::OnDestroy()
{
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
		m_glfwWindow = nullptr;
	}
	CView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CMFCApplication1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


void CMFCApplication1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (m_hWndGL) {
		
		// 调整GLFW子窗口大小与视图客户区匹配
		::SetWindowPos(m_hWndGL, NULL, 0, 0, cx, cy, SWP_NOZORDER);
		glfwMakeContextCurrent(m_glfwWindow);
		glViewport(0, 0, cx, cy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//基本图形生成算法实验部分，假定观察窗口与视口一致。（左下角为原点，右上角为(cx,cy)）
		//使用正交平行投影
		glOrtho(0, cx, //x范围
			0, cy, //y范围
			-10000.0f, 10000.0f); //z范围（深度）
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		GetDocument()->resizing = true;
	}
}
void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	RenderScene(pDoc->m_str);
}
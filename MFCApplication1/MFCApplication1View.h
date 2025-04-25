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

// MFCApplication1View.h: CMFCApplication1View 类的接口
//

#pragma once
#include <memory>
class CGNode;
#include "glIncludes.h"
#include "CCGRenderContext.h"
#include "MFCApplication1Doc.h"
#include <string>

class CMFCApplication1View : public CView, public CCGRenderContext
{
public:
	GLFWwindow* glfwWindow() const { return m_glfwWindow; }
	void ShowPrompt(const std::string& str); //状态栏上显示提示信息
	void ShowCoord(double x, double y); //状态栏上显示坐标信息
	//根据视口坐标获取对应场景坐标（二维）-调用文档类默认相机的转换函数
	glm::dvec3 DCS2WCS(const glm::dvec3& p); //设备坐标转世界坐标
	glm::dvec3 WCS2DCS(const glm::dvec3& p); //世界坐标转设备坐标
	bool AddRenderable(std::shared_ptr<CGNode> r);

protected: // 仅从序列化创建
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument();
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	GLFWwindow* m_glfwWindow = nullptr;
	HWND m_hWndGL = nullptr;
	bool m_bGLInitialized = false;
	bool InitGLFW(); //初始化GLFW
	void RenderScene(CString m_str); //渲染函数
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

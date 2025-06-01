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

// MFCApplication1Doc.h: CMFCApplication1Doc 类的接口
//

#include "vector"
using namespace std;
#pragma once
#include <memory>
#include "pch.h"
class CLeftView;
class CGGroup;
class CGScene;
class CGRenderContext;
class CGNode;

class CMFCApplication1Doc : public CDocument
{
	// 特性
public:
	std::shared_ptr<CGScene> mScene = nullptr;
	// 操作
public:
	bool RenderScene(CGRenderContext* pRC);
	bool AddRenderable(std::shared_ptr<CGNode> r);
protected: // 仅从序列化创建
	CMFCApplication1Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// 特性
public:
	CString m_str;
	CString algo;
	int numOfEdges;
	int radius;
	float angle;
	bool resizing = false;
// 

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnDraw2dLineseg();
	afx_msg void OnUpdateDraw2dLineseg(CCmdUI* pCmdUI);
	afx_msg void OnDraw2dLineLoop();
	afx_msg void OnUpdateDraw2dLineLoop(CCmdUI* pCmdUI);
	afx_msg void OnDraw2dLineStrip();
	afx_msg void OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI);
protected:
	CGGroup* mSelectedGroup = nullptr;
	HTREEITEM mSelectedItem = nullptr;
public:
	CLeftView* GetLeftView();
	void InstToSceneTree(CTreeCtrl* pTree);//实列节点加入场景树
	void InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hInst, CGNode* node);
	void OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem); //场景树中选中节点
	afx_msg void OnMove();
	afx_msg void OnUpdateMove(CCmdUI* pCmdUI);
	afx_msg void OnZoom();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnRotation();
	afx_msg void OnUpdateRotation(CCmdUI* pCmdUI);
	afx_msg void OnDrawBall();
	afx_msg void OnUpdateDrawBall(CCmdUI* pCmdUI);
	afx_msg void OnCylinder();
	afx_msg void OnUpdateCylinder(CCmdUI* pCmdUI);
	void drawBall(int radius, int slice, int stack,bool useSkeleton,int xval,int yval);
	void drawCylinder(int upRadius,int downRadius,int height, int slice, int stack, bool useSkeleton, int xval, int yval);
};

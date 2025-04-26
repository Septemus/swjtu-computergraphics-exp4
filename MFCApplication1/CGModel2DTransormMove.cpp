#include "pch.h"
#include "CGModel2DTransormMove.h"
#include "CGGeometry.h"
#include "MFCApplication1View.h"
CGModel2DTransormMove::CGModel2DTransormMove(GLFWwindow* window,CGGeode* node)
	:UIEventHandler(window),node(node)
{
}
CGModel2DTransormMove::~CGModel2DTransormMove()
{
}
EventType CGModel2DTransormMove::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Model2DTransformMove;
}
int CGModel2DTransormMove::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (window == nullptr)
		return -1;
	CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	CGGeometry* target = (CGGeometry*)node->GetChild(0);
	switch (key) {
		case GLFW_KEY_UP: {
			target->upMove();
			break;
		}
		case GLFW_KEY_RIGHT: {
			target->rightMove();
			break;
		}
		case GLFW_KEY_DOWN: {
			target->downMove();
			break;
		}
		case GLFW_KEY_LEFT: {
			target->leftMove();
			break;
		}
	}
	view->Invalidate(); //客户区需要重绘
	view->UpdateWindow(); //客户区执行重绘
	return key;
}
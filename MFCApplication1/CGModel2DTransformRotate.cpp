#include "pch.h"
#include "CGModel2DTransformRotate.h"
#include "MFCApplication1View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CGGeometry.h"
CGModel2DTransformRotate::CGModel2DTransformRotate(GLFWwindow* window, CGGeode* node)
	:UIEventHandler(window), node(node),pressing(false)
{
}
CGModel2DTransformRotate::~CGModel2DTransformRotate()
{
}
EventType CGModel2DTransformRotate::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Model2DTransformRotate;
}
int CGModel2DTransformRotate::OnMouseButton(GLFWwindow* window, int button, int action, int mods) {
	
	if (window == nullptr)
		return -1;
	CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			view->changeCursor(IDC_HAND);
			pressing = true;
		}
		else if (action == GLFW_RELEASE) {
			view->changeCursor(IDC_ARROW);
			pressing = false;
		}
	}
}
int CGModel2DTransformRotate::OnCursorPos(GLFWwindow* window, double xpos, double ypos) {
	if (pressing) {
		if (window == nullptr)
			return -1;
		CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
		if (view == nullptr)
			return -1;
		glm::dvec3 cur = view->DCS2WCS(glm::dvec3(xpos, ypos, 0));
		CGGeometry* target = (CGGeometry*)node->GetChild(0);
		Cordinate<double>* center = target->getCenter();
		double deltay = cur.y - center->getY();
		double deltax = cur.x - center->getX();
		double r = sqrt(deltax * deltax + deltay * deltay);
		double sina = deltay / r;
		double cosa = deltax / r;
		target->rotate(sina, cosa);
		view->Invalidate(); //客户区需要重绘
		view->UpdateWindow(); //客户区执行重绘
	}
}
#include "pch.h"
#include "CGModel2DTransformZoom.h"
#include "MFCApplication1View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CGGeometry.h"
CGModel2DTransformZoom::CGModel2DTransformZoom(GLFWwindow* window, CGGeode* node)
	:UIEventHandler(window), node(node),pressing(false),dropPoint(nullptr)
{
}
CGModel2DTransformZoom::~CGModel2DTransformZoom()
{
}
EventType CGModel2DTransformZoom::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Model2DTransformZoom;
}
int CGModel2DTransformZoom::OnMouseButton(GLFWwindow* window, int button, int action, int mods) {

	if (window == nullptr)
		return -1;
	CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			view->changeCursor(IDC_HAND);
			pressing = true;
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			glm::dvec3 tmp = glm::dvec3(xpos, ypos, 0);
			tmp = view->DCS2WCS(tmp);
			dropPoint = new Cordinate<double>(tmp.x, tmp.y);
		}
		else if (action == GLFW_RELEASE) {
			view->changeCursor(IDC_ARROW);
			pressing = false;
			delete dropPoint;
			dropPoint = nullptr;
		}
	}
}
int CGModel2DTransformZoom::OnCursorPos(GLFWwindow* window, double xpos, double ypos) {
	if (pressing) {
		if (window == nullptr)
			return -1;
		CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
		if (view == nullptr)
			return -1;
		glm::dvec3 cur = view->DCS2WCS(glm::dvec3(xpos, ypos, 0));
		CGGeometry* target = (CGGeometry*)node->GetChild(0);
		double deltay = cur.y - dropPoint->getY();
		double deltax = cur.x - dropPoint->getX();
		double ratio = fabs(max(deltax, deltay) / 200.0);
		if (ratio > 0.2) {
			target->zoom(ratio);
			view->Invalidate(); //客户区需要重绘
			view->UpdateWindow(); //客户区执行重绘
		}
	}
}
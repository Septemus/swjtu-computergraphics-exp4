#include "pch.h"
#include "CScanline.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"


CScanline::CScanline(GLFWwindow* window)
	:UIEventHandler(window), mStart(0.0, 0.0, 0.0), mEnd(0.0, 0.0, 0.0)
{
	Cordinates = new vector<Cordinate<int>*>();
}

CScanline::~CScanline()
{

	delete Cordinates;
}

EventType CScanline::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Scanline;
}

//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
int CScanline::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			int w, h;
			glfwGetWindowSize(window,&w, &h);
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			Cordinate<int>* clickingPoint = new Cordinate<int>(xpos, h-ypos);
			Cordinates->push_back(clickingPoint);
			glfwMakeContextCurrent(window);
			glfwSwapBuffers(window);
			drawPoint(clickingPoint);
			glfwSwapBuffers(window);
			
		}
	}
}
void CScanline::drawPoint(Cordinate<int>* point) {
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glColor3f(0.8f,0.3f,0.0f);
	glVertex2d(point->getX(), point->getY());
	glEnd();
	glPointSize(1.0f);
}

vector<Cordinate<int>*>* CScanline::getCordinates() {
	return Cordinates;
}
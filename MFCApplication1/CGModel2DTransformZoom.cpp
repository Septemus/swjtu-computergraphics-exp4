#include "pch.h"
#include "CGModel2DTransformZoom.h"
CGModel2DTransformZoom::CGModel2DTransformZoom(GLFWwindow* window, CGGeode* node)
	:UIEventHandler(window), node(node)
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
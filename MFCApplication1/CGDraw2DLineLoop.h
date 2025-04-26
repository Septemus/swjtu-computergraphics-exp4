#pragma once
#include "CGDraw2DLineSeg.h"
class CGDraw2DLineLoop :
    public CGDraw2DLineSeg
{
public:
	CGDraw2DLineLoop(GLFWwindow* window = nullptr);
	virtual EventType GetType() override; //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
protected:
	glm::dvec3 lastDest; //上一个线段的终点
	glm::dvec3 firstPoint; //第一个点
};


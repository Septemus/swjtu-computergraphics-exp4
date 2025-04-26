#pragma once
#include "CGDraw2DLineSeg.h"
class CGDraw2DLineStrip :
    public CGDraw2DLineSeg
{
public:
	CGDraw2DLineStrip(GLFWwindow* window = nullptr);
	virtual EventType GetType() override; //命令类型
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
	int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
protected:
};


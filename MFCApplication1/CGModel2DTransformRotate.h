#pragma once
#include "UIEventHandler.h"
#include "CGGeode.h"
class CGModel2DTransformRotate :
    public UIEventHandler
{
public:
	CGModel2DTransformRotate(GLFWwindow* window = nullptr, CGGeode* node = nullptr);
	~CGModel2DTransformRotate();
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual EventType GetType() override; //命令类型
protected:
	CGGeode* node;
	bool pressing;
};


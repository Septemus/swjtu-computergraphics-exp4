#pragma once
#include "UIEventHandler.h"
#include "CGGeode.h"
#include "Cordinate.h"
class CGModel2DTransformZoom :
    public UIEventHandler
{
public:
	CGModel2DTransformZoom(GLFWwindow* window = nullptr, CGGeode* node = nullptr);
	~CGModel2DTransformZoom();
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual EventType GetType() override; //命令类型
protected:
	CGGeode* node;
	Cordinate<double>* dropPoint;
	bool pressing;
};


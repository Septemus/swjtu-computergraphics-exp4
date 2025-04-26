#pragma once
#include "UIEventHandler.h"
#include "CGGeode.h"
class CGModel2DTransformZoom :
    public UIEventHandler
{
public:
	CGModel2DTransformZoom(GLFWwindow* window = nullptr, CGGeode* node = nullptr);
	~CGModel2DTransformZoom();
	virtual EventType GetType() override; //命令类型
protected:
	CGGeode* node;
};


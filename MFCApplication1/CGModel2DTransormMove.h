#pragma once
#include "UIEventHandler.h"
#include "CGGeode.h"
class CGModel2DTransormMove :
    public UIEventHandler
{
public:
	CGModel2DTransormMove(GLFWwindow* window = nullptr,CGGeode* node=nullptr);
	~CGModel2DTransormMove();
	virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	virtual EventType GetType() override; //命令类型
protected:
	CGGeode* node;
};


#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include "Cordinate.h"
#include "vector"
using namespace std;
class CScanline :
    public UIEventHandler
{
public:
    CScanline(GLFWwindow* window = nullptr);
    ~CScanline();
    virtual EventType GetType() override; //命令类型
    //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    vector<Cordinate<int>*>* getCordinates();
protected:
    glm::dvec3 mStart; //点击的第一点作为线段起点
    glm::dvec3 mEnd; //点击的第二点作为线段终点
    //临时存放当前位置的前一、二光标位置（因为双缓存的原因，橡皮线可能绘制到了前两帧）
    glm::dvec3 mPrePos1, mPrePos2;
    int mMoveCount = 0;
private:
    vector<Cordinate<int>*>* Cordinates;
    void drawPoint(Cordinate<int>* point);
};


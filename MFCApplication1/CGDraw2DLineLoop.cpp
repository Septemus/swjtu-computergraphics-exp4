#include "pch.h"
#include "CGDraw2DLineLoop.h"
#include "MFCApplication1Doc.h" //包含View之前要包含Doc
#include "MFCApplication1View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CGLineSegment.h"
#include "Utils.h"

CGDraw2DLineLoop::CGDraw2DLineLoop(GLFWwindow* window):CGDraw2DLineSeg(window){}
EventType CGDraw2DLineLoop::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Draw2DLineLoop;
}
//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
int CGDraw2DLineLoop::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CMFCApplication1View* view = (CMFCApplication1View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mStep++; //每次单击鼠标左键时操作步骤计数加一
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (mStep == 1) { //第一次单击鼠标左键，记录鼠标点击位置作为将创建线段的起点
				mStart.x = xpos;
				mStart.y = ypos;
				mEnd = mStart;
				mPrePos1 = mEnd;
				mPrePos2 = mEnd;
				firstPoint = mStart;
				view->ShowPrompt("请鼠标左键单击输入直线段的终点"); //通过处理事件的View显示到状态栏
			}
			else if (mStep >= 2) { 
				if (xpos == mStart.x && ypos == mStart.y) {
					view->ShowPrompt("与起点重合，请鼠标左键单击重新输入直线段的终点");
					return -1;
				}
				//判断是否按下SHIFT键，如果是，则根据X、Y方向的增量大小决定绘制水平线或垂直线
				int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS) {
					if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x方向变化小，垂直线
						mEnd.x = mStart.x; //X保持不变
						mEnd.y = ypos;
					}
					else { //x方向变化大，水平线
						mEnd.x = xpos;
						mEnd.y = mStart.y; //Y保持不变
					}
				}
				else { //一般直线段（非水平、垂直），记录终点。
					mEnd.x = xpos;
					mEnd.y = ypos;
				}
				glm::dvec3 start = view->DCS2WCS(mStart);
				glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
				glm::dvec3 end = view->DCS2WCS(mEnd);
				//擦除最后橡皮线
				glEnable(GL_COLOR_LOGIC_OP);
				glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
				glColor3f(0.0f, 0.0f, 1.0f);
				if (mMoveCount == 0) { //第一次移动
					lineDraw<double>(start, end); // 绘制新线
					mPrePos1 = mEnd;
					mPrePos2 = mEnd;
				}
				else if (mMoveCount == 1) { //第二次移动
					lineDraw<double>(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				else {
					lineDraw<double>(start, pre2);// 擦除旧线
					lineDraw<double>(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				glDisable(GL_COLOR_LOGIC_OP);
				glfwSwapBuffers(window);
				//鼠标左键第二次单击，直线段创建的起点、终点已获取。
				//创建对象要注意坐标转换到场景，并设置相应的属性。
//获取起点、终点对应的场景坐标用于创建直线段对象
				view->AddRenderable(std::make_shared<CGLineSegment>(start, end)); //创建添加到场景
				view->Invalidate(); //客户区需要重绘
				view->UpdateWindow(); //
				view->ShowPrompt("请输入直线段的起点"); //状态栏显示
				mStart = mEnd;
			}
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (mStep >= 2) {
				if (xpos == mStart.x && ypos == mStart.y) {
					view->ShowPrompt("与起点重合，请鼠标左键单击重新输入直线段的终点");
					return -1;
				}
				//判断是否按下SHIFT键，如果是，则根据X、Y方向的增量大小决定绘制水平线或垂直线
				int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS) {
					if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x方向变化小，垂直线
						mEnd.x = mStart.x; //X保持不变
						mEnd.y = ypos;
					}
					else { //x方向变化大，水平线
						mEnd.x = xpos;
						mEnd.y = mStart.y; //Y保持不变
					}
				}
				else { //一般直线段（非水平、垂直），记录终点。
					mEnd.x = xpos;
					mEnd.y = ypos;
				}
				glm::dvec3 start = view->DCS2WCS(mStart);
				glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
				glm::dvec3 end = view->DCS2WCS(mEnd);
				//擦除最后橡皮线
				glEnable(GL_COLOR_LOGIC_OP);
				glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
				glColor3f(0.0f, 0.0f, 1.0f);
				if (mMoveCount == 0) { //第一次移动
					lineDraw<double>(start, end); // 绘制新线
					mPrePos1 = mEnd;
					mPrePos2 = mEnd;
				}
				else if (mMoveCount == 1) { //第二次移动
					lineDraw<double>(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				else {
					lineDraw<double>(start, pre2);// 擦除旧线
					lineDraw<double>(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				glm::dvec3 first = view->DCS2WCS(firstPoint);
				lineDraw<double>(end, first);
				glDisable(GL_COLOR_LOGIC_OP);
				glfwSwapBuffers(window);
				mStep = 0; //设为0可重写开始绘制线段而不用点击命令面板上的线段按钮
				mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
				//鼠标左键第二次单击，直线段创建的起点、终点已获取。
				//创建对象要注意坐标转换到场景，并设置相应的属性。
				//获取起点、终点对应的场景坐标用于创建直线段对象
				view->AddRenderable(std::make_shared<CGLineSegment>(start, end)); //创建添加到场景
				view->AddRenderable(std::make_shared<CGLineSegment>(end, first)); //创建添加到场景
				//view->Invalidate(); //客户区需要重绘
				//view->UpdateWindow(); 
				view->ShowPrompt("请输入直线段的起点"); //状态栏显示			
			}
		}
	}
	return 0;
}
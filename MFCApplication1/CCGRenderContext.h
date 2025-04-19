#pragma once
#include "glIncludes.h"
#include "Cordinate.h"
#include <vector>
#define pi 3.141592653589793
using namespace std;
struct MyColor {
	float r;
	float g;
	float b;
};
class CCGRenderContext
{
public:
	CCGRenderContext();
	virtual ~CCGRenderContext();
	void drawEqualPolygon(const Cordinate<int>* center, int numOfEdges,CString algo=CString(_T("dda")));
	template<typename T>
	void drawPolygon(vector<Cordinate<T>*>* const vertices, CString algo = CString(_T("dda"))) {
		Cordinate<T>* last = NULL;
		Cordinate<T>* first = NULL;
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		if (algo.CompareNoCase(_T("dda")) == 0) {
			color = glm::vec3(1.0f, 0.0f, 0.0f);
		}
		else if (algo.CompareNoCase(_T("midpoint")) == 0) {
			color = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else if (algo.CompareNoCase(_T("bresenham")) == 0) {
			color = glm::vec3(0.0f, 0.9f, 0.9f);
		}
		for (vector<Cordinate<T>*>::const_iterator i = vertices->begin(); i != vertices->end();++i) {
			if (last != NULL) {
				lineDrawAlgorithm(last, (*i), color, algo);
			}
			else {
				first = (*i);
			}
			last = (*i);
		}
		lineDrawAlgorithm(last, first, color, algo);
	}
	void drawArc(const Cordinate<int>* center, int radius, float angle, glm::vec3 color, CString algo = CString(_T("midpoint")));
	void drawFilledPolygonByScanline(vector<Cordinate<int>*>* cordinatesOfVertices);
	std::vector<Cordinate<int>*>* MidPointCircle(const Cordinate<int>* center, int radius);
	std::vector<Cordinate<int>*>* BresenhamCircle(const Cordinate<int>* center, int radius);
	template<typename T>
	std::vector<Cordinate<T>*>* DDALine(Cordinate<T>* start, Cordinate<T>* end) {
		//以下是绘制代码示例：用于其他算法参考，可根据自己的涉及进行修改
		std::vector<Cordinate<T>*>* vec=new std::vector<Cordinate<T>*>();
		int steps;
		T dx = end->getX() - start->getX();
		T dy = end->getY() - start->getY();
		if (fabs(dx) >= fabs(dy))
			steps = fabs(dx);
		else
			steps = fabs(dy);
		if (steps == 0)
			return NULL;
		float x = start->getX(), y = start->getY();
		float xincre = (float)dx / steps, yincre = (float)dy / steps;
		for (int i = 0; i <= steps; i++)
		{
			vec->push_back(new Cordinate<T>((int)(x+0.5),(int)( y+0.5)));
			x = x + xincre;
			y = y + yincre;
		}
		return vec;
	}

	template<typename T>
	std::vector<Cordinate<T>*>* Bresenham(Cordinate<T>* start, Cordinate<T>* end) {
		//以下是绘制代码示例：用于其他算法参考，可根据自己的涉及进行修改
		std::vector<Cordinate<T>*>* vec = new std::vector<Cordinate<T>*>();
		T dx = end->getX() - start->getX();
		T dy = end->getY() - start->getY();
		T delta1 = 2 * (dy),delta2=2*(dy)-2*(dx);
		T d = 2 * (dy) - (dx);
		T x = start->getX(),y=start->getY();
		while (x <= end->getX()) {
			vec->push_back(new Cordinate<T>((int)(x + 0.5), (int)(y + 0.5))); //在(x,y)处，以颜色color绘像素
			x++;
			if (d < 0) {
				d += delta1;
			}
			else {
				++y;
				d += delta2;
			}
		}
		return vec;
	}

	template<typename T>
	std::vector<Cordinate<T>*>* MidPointLine(Cordinate<T>* start, Cordinate<T>* end) {
		std::vector<Cordinate<T>*>* vec=new std::vector<Cordinate<T>*>();
		T a = start->getY() - end->getY(), b = end->getX() - start->getX();
		T d = 2 * a + b;
		T delta1 = 2 * a;
		T delta2 = 2 * (a + b);
		T x = start->getX(), y = start->getY();
		while (x <= end->getX()) {
			vec->push_back(new Cordinate<T>((int)(x + 0.5), (int)(y + 0.5))); //在(x,y)处，以颜色color绘像素
			if (d < 0) {
				x++;
				y++;
				d += delta2;
			}
			else {
				x++;
				d += delta1;
			}
		}
		return vec;
	}

	template<typename T>
	void lineDrawAlgorithm(Cordinate<T>*  start,Cordinate<T>*  end, glm::vec3 color,CString algo=CString(_T("dda"))) {
		start = new Cordinate<T>(start);
		end = new Cordinate<T>(end);
		if (start->getX() > end->getX()) {
			Cordinate<T>* tmp = start;
			start = end;
			end = tmp;
		}
		T dx = end->getX() - start->getX();
		T dy = end->getY() - start->getY();
		boolean xy_symmetry = false;
		boolean y_symmetry = false;
		if (dy < 0) {
			y_symmetry = true;
			start->setY(-start->getY());
			end->setY(-end->getY());
		}
		if (fabs(dx) < fabs(dy)) {
			T tmp = start->getX();
			start->setX(start->getY());
			start->setY(tmp);
			tmp = end->getX();
			end->setX(end->getY());
			end->setY(tmp);
			xy_symmetry = true;
		}
		std::vector<Cordinate<T>*>* vec = NULL;
		if (algo.CompareNoCase(CString(_T("dda"))) == 0) {
			vec = DDALine(start,end);
		}
		else if (algo.CompareNoCase( CString( _T("midpoint") ) ) == 0) {
			vec = MidPointLine(start,end);
		}
		else if (algo.CompareNoCase(_T("bresenham")) == 0) {
			vec = Bresenham(start, end);
		}
		if (vec != NULL) {
			glColor3f(color.r, color.g, color.b);
			glBegin(GL_POINTS);
			for (std::vector<Cordinate<T>*>::iterator i = vec->begin();i != vec->end();++i) {
				T x = (*i)->getX(), y = (*i)->getY();
				if (xy_symmetry) {
					T tmp = x;
					x = y;
					y = tmp;
				}
				if (y_symmetry) {
					y = -y;
				}
				glVertex2d((int)(x + 0.5), (int)(y + 0.5)); //在(x,y)处，以颜色color绘像素
			}
			glEnd();
			delete vec;
		}
	}
};
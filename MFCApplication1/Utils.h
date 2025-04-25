#pragma once
#include <vector>
#include "Cordinate.h"
#include "glIncludes.h"

using namespace std;
template<typename T>
vector<Cordinate<T>*>* MidPointLine(Cordinate<T>* start, Cordinate<T>* end) {
	std::vector<Cordinate<T>*>* vec = new std::vector<Cordinate<T>*>();
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
vector<Cordinate<T>*>* lineDrawAlgorithm(Cordinate<T>* start, Cordinate<T>* end, vector<Cordinate<T>*>* (*algo)(Cordinate<T>* start, Cordinate<T>* end)=MidPointLine) {
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
	vector<Cordinate<T>*>* vec = algo(start, end);
	if (vec != NULL){
		for (vector<Cordinate<T>*>::iterator i = vec->begin();i != vec->end();++i) {
			T x = (*i)->getX(), y = (*i)->getY();
			if (xy_symmetry) {
				T tmp = x;
				x = y;
				y = tmp;
			}
			if (y_symmetry) {
				y = -y;
			}
			(*i)->setX(x);
			(*i)->setY(y);
		}
	}
	return vec;
}
template<typename T>
void lineDraw(vector<Cordinate<T>*>* cordinates) {
	glBegin(GL_POINTS);
	for (std::vector<Cordinate<T>*>::iterator i = cordinates->begin();i != cordinates->end();++i) {
		T x = (*i)->getX(), y = (*i)->getY();
		glVertex2d(x, y); //在(x,y)处，以颜色color绘像素
	}
	glEnd();
	delete cordinates;
}

template<typename T>
void lineDraw(Cordinate<T>* start, Cordinate<T>* end) {
	lineDraw(lineDrawAlgorithm(start, end));
}


template<typename T>
void lineDraw(glm::dvec3& s, glm::dvec3& e) {
	lineDraw(new Cordinate<T>(s.x, s.y), new Cordinate<T>(e.x, e.y));
}

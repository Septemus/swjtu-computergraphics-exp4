#include "pch.h"
#include "CCGRenderContext.h"
CCGRenderContext::CCGRenderContext()
{
}
CCGRenderContext::~CCGRenderContext()
{
}

void CCGRenderContext::drawEqualPolygon(const Cordinate<int>* center,int numOfEdges,CString algo)
{
	vector<Cordinate<float>*>* vec = new vector<Cordinate<float>*>();
	for (int i = 0;i < numOfEdges;++i) {
		float x = center->getX() + 100 * cos((2 * pi * i) / numOfEdges);
		float y = center->getY() + 100 * sin((2 * pi * i) / numOfEdges);
		vec->push_back(new Cordinate<float>(x, y));
	}
	drawPolygon(vec,algo);
	delete vec;
}
void CCGRenderContext::drawArc(const Cordinate<int>* center, int radius, float angle, glm::vec3 color, CString algo) {
	std::vector<Cordinate<int>*>* dots = NULL;
	if (algo.CompareNoCase(_T("midpoint"))==0) {
		dots = MidPointCircle(center, radius);
	}
	else if(algo.CompareNoCase(_T("bresenham")) == 0) {
		dots = BresenhamCircle(center, radius);
	}
	std::vector<Cordinate<int>*> * dots_area[9] = {};
	for (int i = 0;i < 9;++i) {
		dots_area[i] = new std::vector<Cordinate<int>*>();
	}
	for (std::vector<Cordinate<int>*>::iterator i = dots->begin();i != dots->end();++i) {
		int relative_x = (*i)->getX()-center->getX();
		int relative_y = (*i)->getY()-center->getY();
		if (relative_y > 0) {
			if (relative_x > 0) {
				if (relative_x > relative_y) {
					dots_area[0]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
				else {
					dots_area[1]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
			}
			else {
				if (abs(relative_x) > relative_y) {
					dots_area[3]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
				else {
					dots_area[2]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
			}
		}
		else {
			if (relative_x < 0) {
				if (abs(relative_x) > abs(relative_y)) {
					dots_area[4]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
				else {

					dots_area[5]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
			}
			else {
				
				if (relative_x > abs(relative_y)) {
					dots_area[7]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
				else {
					dots_area[6]->push_back(new Cordinate<int>(relative_x, relative_y));
				}
			}
		}
	}
	int numberOfFilledAreas = (int)angle / 45;
	int remainingAngle = angle - numberOfFilledAreas * 45;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	for (int idx = 0;idx < numberOfFilledAreas;++idx) {
		for (std::vector<Cordinate<int>*>::iterator i = dots_area[idx]->begin();i != dots_area[idx]->end();++i) {
			glVertex2d(center->getX() + (*i)->getX(), center->getY() + (*i)->getY()); //在(x,y)处，以颜色color绘像素
		}
	}
	if (remainingAngle != 0) {
		Cordinate<int>* cut_off_point = new Cordinate<int>((int)(radius * cos(2 * pi * angle / 360)), (int)(radius * sin(2 * pi * angle / 360)));
		int cut_off_index = -1;
		for (int i = 0;i < dots_area[numberOfFilledAreas]->size();++i) {
			if (dots_area[numberOfFilledAreas]->at(i)->getX() == cut_off_point->getX()) {
				cut_off_index = i;
			}
		}
		if (cut_off_index != -1) {
			if (numberOfFilledAreas % 2==0) {
				for (int i = 0;i < cut_off_index;++i) {
					glVertex2d(center->getX() + dots_area[numberOfFilledAreas]->at(i)->getX(), center->getY() + dots_area[numberOfFilledAreas]->at(i)->getY());
				}
			}
			else {
				for (int i = cut_off_index;i < dots_area[numberOfFilledAreas]->size();++i) {
					glVertex2d(center->getX() + dots_area[numberOfFilledAreas]->at(i)->getX(), center->getY() + dots_area[numberOfFilledAreas]->at(i)->getY());
				}
			}
		}
	}
	glEnd();
	delete dots;
	for (int i = 0;i < 9;++i) {
		delete dots_area[i];
	}
}

std::vector<Cordinate<int>*>* CCGRenderContext::MidPointCircle(const Cordinate<int>* center, int radius) {
	std::vector<Cordinate<int>*>* vec = new std::vector<Cordinate<int>*>();
	int x, y, d;
	x = 0, y = radius;
	d = 5 - 4 * radius;
	int dir[4][2] = {
		{ 1, 1 }, {  1,-1 },
		{ -1,1 }, { -1,-1 }
	};
	for (int i = 0; i < 2; i++) {
		vec->push_back(new Cordinate<int>(center->getX() + x * dir[i][0], center->getY() + y * dir[i][1]));
		vec->push_back(new Cordinate<int>(center->getX() + y * dir[i][0], center->getY() + x * dir[i][1]));
	}
	while (x <= y) {
		if (d >= 0) {
			x += 1;
			y -= 1;
			d += 8 * (x - y) + 20;
		}
		else {
			x += 1;
			d += 8 * x + 12;
		}
		for (int i = 0; i < 4; i++) {
			vec->push_back(new Cordinate<int>(center->getX() + x * dir[i][0], center->getY() + y * dir[i][1]));
			vec->push_back(new Cordinate<int>(center->getX() + y * dir[i][0], center->getY() + x * dir[i][1]));
		}
	}
	return vec;
}

std::vector<Cordinate<int>*>* CCGRenderContext::BresenhamCircle(const Cordinate<int>* center, int radius) {
	std::vector<Cordinate<int>*>* vec = new std::vector<Cordinate<int>*>();
	int x, y;
	x = 0, y = radius;
	int d = 3 - 2 * radius;
	int dir[4][2] = {
	{ 1, 1 }, { 1,-1 },
	{ -1,1}, {-1,-1 }
	};		//使用循环来计算对称的区域
	for (int i = 0; i < 2; i++) {
		vec->push_back(new Cordinate<int>(center->getX(), center->getY() + y * dir[i][1]));
		vec->push_back(new Cordinate<int>(center->getX() + y * dir[i][0], center->getY()));
	}
	while (x < y) {
		if (d >= 0) {
			x += 1;
			y -= 1;
			d += 4 * (x - y) + 10;
		}
		else {
			x += 1;
			d += 4 * x + 6;
		}
		for (int i = 0; i < 4; i++) {
			vec->push_back(new Cordinate<int>(center->getX() + x * dir[i][0], center->getY() + y * dir[i][1]));
			vec->push_back(new Cordinate<int>(center->getX() + y * dir[i][0], center->getY() + x * dir[i][1]));
		}
	}
	return vec;
}

void CCGRenderContext::drawFilledPolygonByScanline(const vector<Cordinate<int>*>* cordinatesOfVertices) {

}
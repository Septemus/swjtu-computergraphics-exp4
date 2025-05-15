#include "pch.h"
#include "CGLineSegment.h"
#include "Utils.h"
IMPLEMENT_SERIAL(CGLineSegment, CGGeometry, 1)
CGLineSegment::CGLineSegment()
	: mStart(glm::dvec3(0.0, 0.0, 0.0)), mEnd(glm::dvec3(0.0, 0.0, 0.0))
{
	oStart = mStart;
	oEnd = mEnd;
}
CGLineSegment::CGLineSegment(const glm::dvec3& start, const glm::dvec3& end)
	: mStart(start), mEnd(end)
{
	oStart = mStart;
	oEnd = mEnd;
}
CGLineSegment::~CGLineSegment()
{
}
void CGLineSegment::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
//渲染
bool CGLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	glColor3f(1.0f, 1.0f, 1.0f); // 白色
	lineDraw<double>(mStart, mEnd);
	return true;
}

void CGLineSegment::leftMove() {
	mStart.x -= 5;
	mEnd.x -= 5;
	oStart = mStart;
	oEnd = mEnd;
};
void CGLineSegment::upMove() {
	mStart.y += 5;
	mEnd.y += 5;
	oStart = mStart;
	oEnd = mEnd;
};
void CGLineSegment::downMove() {
	mStart.y -= 5;
	mEnd.y -= 5;
	oStart = mStart;
	oEnd = mEnd;
};
void CGLineSegment::rightMove() {
	mStart.x += 5;
	mEnd.x += 5;
	oStart = mStart;
	oEnd = mEnd;
};
void CGLineSegment::rotate(double sina, double cosa) {
	Cordinate<double>* midpoint = getCenter();
	double x1=mStart.x - midpoint->getX();
	double y1=mStart.y - midpoint->getY();
	double r1 = sqrt(x1 * x1 + y1 * y1);
	mStart.x = r1*cosa;
	mStart.y = r1*sina;
	mEnd.x = -mStart.x;
	mEnd.y = -mStart.y;
	mStart.x += midpoint->getX();
	mStart.y += midpoint->getY();
	mEnd.x += midpoint->getX();
	mEnd.y += midpoint->getY();
	oStart = mStart;
	oEnd = mEnd;
	delete midpoint;
}
void CGLineSegment::zoom(double ratio) {
	Cordinate<double>* midpoint = getCenter();
	double deltax = oStart.x - midpoint->getX();
	double deltay = oStart.y - midpoint->getY();
	mStart.x = deltax * ratio + midpoint->getX();
	mStart.y = deltay * ratio + midpoint->getY();
	deltax = oEnd.x - midpoint->getX();
	deltay = oEnd.y - midpoint->getY();
	mEnd.x = deltax * ratio + midpoint->getX();
	mEnd.y = deltay * ratio + midpoint->getY();
	delete midpoint;
}
Cordinate<double>* CGLineSegment::getCenter() {
	return new Cordinate<double>((mStart.x + mEnd.x) / 2, (mStart.y + mEnd.y) / 2);
}
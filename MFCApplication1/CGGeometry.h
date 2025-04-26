#pragma once
#include "CGRenderable.h"
#include "Cordinate.h"
class CGGeometry : public CGRenderable
{
	DECLARE_SERIAL(CGGeometry)
public:
	CGGeometry();
	virtual ~CGGeometry();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual void leftMove();
	virtual void upMove();
	virtual void rightMove();
	virtual void downMove();
	virtual void rotate(double sina, double cosa) {}
	virtual Cordinate<double>* getCenter() { return nullptr; };
protected:
};
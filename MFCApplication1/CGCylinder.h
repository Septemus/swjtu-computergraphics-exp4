#pragma once
#include "CGRenderable.h"
#include "pch.h"
class TessellationHints;
class CGCylinder :
    public CGRenderable
{
    DECLARE_SERIAL(CGCylinder)
public:
    CGCylinder() {}
    CGCylinder(int upRadius, int downRadius, int height);
    virtual ~CGCylinder() {}
    void setTessellationHints(std::shared_ptr<TessellationHints> hints);
    TessellationHints* tessellationHints() { return mTessellationHints.get(); }
    const TessellationHints* tessellationHints() const { return mTessellationHints.get(); }
protected:
    virtual void buildDisplayList(); //重写基类虚函数
protected:
    std::shared_ptr<TessellationHints> mTessellationHints = nullptr;
    int mUpRadius = 1;
    int mDownRadius = 1;
    int mHeight = 100;
};


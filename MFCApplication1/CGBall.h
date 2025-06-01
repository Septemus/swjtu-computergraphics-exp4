#pragma once
#include "pch.h"
#include "CGRenderable.h"
class TessellationHints;
class CGBall :
    public CGRenderable
{
    DECLARE_SERIAL(CGBall)
public:
    CGBall() {}
    virtual ~CGBall() {}
    void setTessellationHints(std::shared_ptr<TessellationHints> hints);
    TessellationHints* tessellationHints() { return mTessellationHints.get(); }
    const TessellationHints* tessellationHints() const { return mTessellationHints.get(); }
protected:
    virtual void buildDisplayList(); //重写基类虚函数
protected:
    std::shared_ptr<TessellationHints> mTessellationHints = nullptr;
    int mRadius = 1;
};


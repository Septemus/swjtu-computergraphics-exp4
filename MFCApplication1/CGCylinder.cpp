#include "pch.h"
#include "CGCylinder.h"
#include "TessellationHints.h"
#include "Utils.h"
IMPLEMENT_SERIAL(CGCylinder, CGRenderable, 1)
CGCylinder::CGCylinder(int upRadius, int downRadius, int height):mUpRadius(upRadius),mDownRadius(downRadius),mHeight(height) {}
void CGCylinder::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}

void CGCylinder::buildDisplayList()
{
	TessellationHints* hints = tessellationHints();
	double sliceDelta = 2.0 * PI / hints->targetSlices();
	double stackDelta = (double)mHeight / hints->targetStacks();
	for (int stack = 0; stack < hints->targetStacks() - 1; ++stack) {
		double rPlatform = mDownRadius + ((double)stack / hints->targetStacks()) * (mUpRadius - mDownRadius);
		double rPlatformNext = mDownRadius + ((double)(stack+1)/ hints->targetStacks()) * (mUpRadius - mDownRadius);
		const double y = stack*stackDelta;
		const double yNext = (stack+1)*stackDelta;
		glBegin(GL_QUAD_STRIP);
		for (int slice = 0; slice <= hints->targetSlices(); ++slice) {
			double theta = slice * sliceDelta;
			double x = cos(theta) * rPlatform;
			double z = sin(theta) * rPlatform;
			glNormal3d(x, y, z);
			glVertex3d(x, y, z);
			double xNext = cos(theta) * rPlatformNext;
			double zNext = sin(theta) * rPlatformNext;
			glNormal3d(xNext, yNext, zNext);
			glVertex3d(xNext, yNext, zNext);
		}
		glEnd();
	}
	glBegin(GL_POLYGON);
	for (int slice = 0; slice <= hints->targetSlices(); ++slice) {
		double theta = slice * sliceDelta;
		glNormal3d(0, -1, 0);
		glVertex3d(cos(theta) * mDownRadius, 0, sin(theta) * mDownRadius);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int slice = 0; slice <= hints->targetSlices(); ++slice) {
		double theta = slice * sliceDelta;
		glNormal3d(0, 1, 0);
		glVertex3d(cos(theta) * mUpRadius, mHeight, sin(theta) * mUpRadius);
	}
	glEnd();
}

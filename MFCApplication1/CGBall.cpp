#include "pch.h"
#include "CGBall.h"
#include "TessellationHints.h"
#include "Utils.h"
IMPLEMENT_SERIAL(CGBall, CGRenderable, 1)
void CGBall::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}

void CGBall::buildDisplayList()
{
	TessellationHints* hints = tessellationHints();
	double sliceDelta = 2.0 * PI / hints->targetSlices(); 
	double stackDelta = PI / hints->targetStacks();
	for (int stack = 0; stack< hints->targetStacks()-1; ++stack) {
		double phi = stack * stackDelta-(0.5*PI);
		double phiNext = phi+stackDelta;
		double sinPhi = sin(phi);
		double cosPhi = cos(phi);
		double sinPhiNext = sin(phiNext);
		double cosPhiNext = cos(phiNext);
		const double y = mRadius * sinPhi;
		const double yNext = mRadius * sinPhiNext;
		glBegin(GL_QUAD_STRIP);
		for (int slice = 0; slice <= hints->targetSlices(); ++slice) {
			double theta = slice * sliceDelta;
			double x = cos(theta) * mRadius * cosPhi;
			double z = sin(theta) * mRadius * cosPhi;
			glNormal3d(x / mRadius, y / mRadius, z / mRadius);
			glVertex3d(x, y, z);
			double xNext = cos(theta) * mRadius * cosPhiNext;
			double zNext = sin(theta) * mRadius * cosPhiNext;
			glNormal3d(xNext / mRadius, yNext / mRadius, zNext / mRadius);
			glVertex3d(xNext, yNext, zNext);
		}
		glEnd();
	}
	for (int slice = 0; slice <= hints->targetSlices(); ++slice) {
		glBegin(GL_LINE_STRIP);
		glNormal3d(0, -1, 0);
		glVertex3d(0, -mRadius, 0);
		for (int stack = 0; stack < hints->targetStacks(); ++stack) {
			double phi = stack * stackDelta - (0.5 * PI);
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);
			const double y = mRadius * sinPhi;
			double theta = slice * sliceDelta;
			double x = cos(theta) * mRadius * cosPhi;
			double z = sin(theta) * mRadius * cosPhi;
			glNormal3d(x / mRadius, y / mRadius, z / mRadius);
			glVertex3d(x, y, z);
		}
		glNormal3d(0, 1, 0);
		glVertex3d(0, mRadius, 0);
		glEnd();
	}
}

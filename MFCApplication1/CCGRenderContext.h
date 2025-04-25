#pragma once
#include "glIncludes.h"
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
};
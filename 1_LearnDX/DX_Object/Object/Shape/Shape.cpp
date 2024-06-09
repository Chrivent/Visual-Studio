#include "framework.h"

Shape::Shape(float x, float y) : pos_x(x), pos_y(y), VB(nullptr)
{
}

Shape::~Shape()
{
	if (VB != nullptr)
		VB->Release();
}

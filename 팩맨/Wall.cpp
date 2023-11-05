#include "Wall.h"

void Wall::Draw(HDC hdc)
{
	DrawRectangleEmpty(hdc, transform, 5, W_SKYBLUE);
	DrawRectangleEmpty(hdc, transform, 3, W_BLUE);
}

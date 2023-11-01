#include "Wall.h"

void Wall::Draw(HDC hdc)
{
	wMecro::DrawRectangleEmpty(hdc, transform, 5, W_SKYBLUE);
	wMecro::DrawRectangleEmpty(hdc, transform, 3, W_BLUE);
}

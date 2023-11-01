#include "Path.h"

Path::Path()
{
	debugVisit = false;
	debugToGo = false;
}

void Path::Draw(HDC hdc)
{
	DrawDebug(hdc);
}

void Path::DrawDebug(HDC hdc)
{
	if (debugVisit)
		wMecro::DrawRectangle(hdc, transform, debugToGo ? W_GREEN : W_GRAY);
}

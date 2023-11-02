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
	{
		COLORREF color = RGB(index % 3 == 2 ? 128 : 0, index % 3 == 0 ? 128 : 0, index % 3 == 1 ? 128 : 0);
		wMecro::DrawRectangle(hdc, transform, debugToGo ? color : RGB(64, 64, 64));
	}
}

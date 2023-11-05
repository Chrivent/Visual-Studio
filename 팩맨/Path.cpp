#include "Path.h"

Path::Path()
{
	index = 0;
	debugVisit = false;
	debugToGo = false;
}

void Path::Draw(HDC hdc)
{
	DrawDebug(hdc);
}

void Path::DrawDebug(HDC hdc) const
{
	if (debugVisit)
	{
		const COLORREF color = RGB(index % 3 == 2 ? 128 : 0, index % 3 == 0 ? 128 : 0, index % 3 == 1 ? 128 : 0);
		DrawRectangle(hdc, transform, debugToGo ? color : RGB(64, 64, 64));
	}
}

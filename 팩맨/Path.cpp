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
		COLORREF color;
		switch (index % 4)
		{
		case 0:
			color = RGB(0, 128, 0);
			break;
		case 1:
			color = RGB(0, 0, 128);
			break;
		case 2:
			color = RGB(128, 0, 0);
			break;
		case 3:
			color = RGB(128, 128, 0);
			break;
		}

		DrawRectangle(hdc, transform, debugToGo ? color : RGB(64, 64, 64));
	}
}

#include<Windows.h>
#include "resource.h"

#pragma warning(disable: 28251)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawPolygon");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);

		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

enum SHAPE
{
	SHAPE_NULL,
	SHAPE_CIRCLE,
	SHAPE_RECTANGLE,
	SHAPE_LINE
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	HPEN myPen;
	HPEN oldPen;

	HBRUSH myBrush;
	HBRUSH oldBrush;

	static SHAPE shape;
	static COLORREF color;
	static RECT size;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000 / 60, NULL);

		size.left = 40;
		size.right = 200;
		size.top = 40;
		size.bottom = 200;

		shape = SHAPE_NULL;
		color = RGB(255, 0, 0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		return 0;

	case WM_PAINT:
		GetClientRect(hWnd, &rt);

		hdc = BeginPaint(hWnd, &ps);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, rt.right - rt.left, rt.bottom - rt.top);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		myBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(g_MemDC, myBrush);

		myPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		oldPen = (HPEN)SelectObject(g_MemDC, myPen);

		Rectangle(g_MemDC, rt.left, rt.top, rt.right, rt.bottom);

		SelectObject(g_MemDC, oldBrush);
		DeleteObject(myBrush);

		SelectObject(g_MemDC, oldPen);
		DeleteObject(myPen);

		//±×¸®±â
		myPen = CreatePen(PS_SOLID, 4, color);
		oldPen = (HPEN)SelectObject(g_MemDC, myPen);

		switch (shape)
		{
		case SHAPE_CIRCLE:
			myBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(g_MemDC, myBrush);

			Ellipse(g_MemDC, size.left, size.top, size.right, size.bottom);

			SelectObject(g_MemDC, oldBrush);
			DeleteObject(myBrush);
			break;

		case SHAPE_RECTANGLE:
			myBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(g_MemDC, myBrush);

			Rectangle(g_MemDC, size.left, size.top, size.right, size.bottom);

			SelectObject(g_MemDC, oldBrush);
			DeleteObject(myBrush);
			break;

		case SHAPE_LINE:
			MoveToEx(g_MemDC, size.left, size.top, NULL);
			LineTo(g_MemDC, size.right, size.bottom);
			break;
		}

		SelectObject(g_MemDC, oldPen);
		DeleteObject(myPen);
		//

		BitBlt(hdc, 0, 0, rt.right - rt.left, rt.bottom - rt.top, g_MemDC, 0, 0, SRCCOPY);

		SelectObject(g_MemDC, g_hOld);
		DeleteObject(g_hBitmap);
		DeleteDC(g_MemDC);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DRAW_CIRCLE_RED:
			shape = SHAPE_CIRCLE;
			color = RGB(255, 0, 0);
			break;

		case ID_DRAW_CIRCLE_GREEN:
			shape = SHAPE_CIRCLE;
			color = RGB(0, 255, 0);
			break;

		case ID_DRAW_CIRCLE_BLUE:
			shape = SHAPE_CIRCLE;
			color = RGB(0, 0, 255);
			break;

		case ID_DRAW_RECTANGLE_RED:
			shape = SHAPE_RECTANGLE;
			color = RGB(255, 0, 0);
			break;

		case ID_DRAW_RECTANGLE_GREEN:
			shape = SHAPE_RECTANGLE;
			color = RGB(0, 255, 0);
			break;

		case ID_DRAW_RECTANGLE_BLUE:
			shape = SHAPE_RECTANGLE;
			color = RGB(0, 0, 255);
			break;

		case ID_DRAW_LINE_RED:
			shape = SHAPE_LINE;
			color = RGB(255, 0, 0);
			break;

		case ID_DRAW_LINE_GREEN:
			shape = SHAPE_LINE;
			color = RGB(0, 255, 0);
			break;

		case ID_DRAW_LINE_BLUE:
			shape = SHAPE_LINE;
			color = RGB(0, 0, 255);
			break;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);

		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
#include<Windows.h>
#include<tchar.h>
#include "resource.h"

#pragma warning(disable: 28251)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("°è»ê±â");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, TEXT("asdf"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);

		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	WCHAR word[100];

	GetDlgItemText(hDlg, IDC_NUM1, word, 100);

	double num1 = _wtof(word);

	GetDlgItemText(hDlg, IDC_NUM2, word, 100);

	double num2 = _wtof(word);

	switch (iMessage)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ADD:
			swprintf_s(word, TEXT("%f"), num1 + num2);

			SetDlgItemText(hDlg, IDC_VAR, word);
			break;

		case IDC_SUBTRACT:
			swprintf_s(word, TEXT("%f"), num1 - num2);

			SetDlgItemText(hDlg, IDC_VAR, word);
			break;

		case IDC_MULTIPLY:
			swprintf_s(word, TEXT("%f"), num1 * num2);

			SetDlgItemText(hDlg, IDC_VAR, word);
			break;

		case IDC_DIVIDE:
			_stprintf_s(word, TEXT("%f"), num1 / num2);

			SetDlgItemText(hDlg, IDC_VAR, word);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;
		}
	}

	return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	HBRUSH myBrush;
	HBRUSH oldBrush;

	HPEN myPen;
	HPEN oldPen;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000 / 60, NULL);
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
		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rt);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		myBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(g_MemDC, myBrush);

		myPen = CreatePen(BS_SOLID, 1, RGB(255, 255, 255));
		oldPen = (HPEN)SelectObject(g_MemDC, myPen);

		Rectangle(g_MemDC, rt.left, rt.top, rt.right, rt.bottom);

		SelectObject(g_MemDC, oldBrush);
		DeleteObject(myBrush);

		SelectObject(g_MemDC, oldPen);
		DeleteObject(myPen);

		//

		//

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, g_MemDC, 0, 0, SRCCOPY);

		SelectObject(g_MemDC, g_hOld);
		DeleteObject(g_hBitmap);
		DeleteDC(g_MemDC);

		EndPaint(hWnd, &ps);

		return 0;

	case WM_LBUTTONDOWN:
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);

		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
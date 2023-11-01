#include<Windows.h>
#include "resource.h"
#include "PacMan.h"

#pragma warning(disable: 28251)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static wMecro::Transform clientTransform;
	//static Scale clientScale = { 760, 880 };
	static Scale clientScale = { 723, 841 };
	static Position clientPosition = { 0, 0 };
	static PacMan pacMan(clientScale.width, clientScale.height);

	switch (iMessage)
	{
	case WM_CREATE:
		//clientPosition.x = (wMecro::GetWindowTransform(hWnd).scale.width - clientScale.width) / 2;
		//clientPosition.y = (wMecro::GetWindowTransform(hWnd).scale.height - clientScale.height) / 2;

		clientTransform.position = clientPosition;
		clientTransform.scale = clientScale;

		wMecro::SetClientTransform(hWnd, clientTransform);

		SetTimer(hWnd, 1, 15, NULL);
		SetTimer(hWnd, 2, 30, NULL);
		SetTimer(hWnd, 3, 1, NULL);
		SetTimer(hWnd, 4, 1, NULL);

		pacMan.playerSpeed = 5;
		pacMan.enemySpeed = 3;

		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);

		PostQuitMessage(0);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case 2:
			pacMan.PlayerGaspUpdate();
			break;

		case 3:
			pacMan.PlayerMoveUpdate();
			break;

		case 4:
			pacMan.EnemyMoveUpdate();
			break;
		}
		return 0;

	case WM_PAINT:
		pacMan.Paint(hWnd);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			pacMan.SetPlayerDirection(Left);
			break;
		case VK_RIGHT:
			pacMan.SetPlayerDirection(Right);
			break;
		case VK_UP:
			pacMan.SetPlayerDirection(Up);
			break;
		case VK_DOWN:
			pacMan.SetPlayerDirection(Down);
			break;
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DEBUG:
			pacMan.debug = !pacMan.debug;
			break;
		}
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
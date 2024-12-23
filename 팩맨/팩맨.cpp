﻿#include<Windows.h>
#include "resource.h"
#include "Pacman.h"

#pragma warning(disable: 28251)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Pacman");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	HACCEL hAccel;

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
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);

			DispatchMessage(&Message);
		}
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static wMecro::Transform clientTransform;
	static int cellSize = 40;
	static Scale clientScale = { WIDTH * cellSize, HEIGHT * cellSize };
	static Position clientPosition = { 0, 0 };
	static Pacman pacman(clientScale);
	static WPARAM key;

	static Scale windowScale;
	static Position windowPosition;

	switch (iMessage)
	{
	case WM_CREATE:
		clientTransform.position = clientPosition;
		clientScale.height += pacman.GetScoreTextTransform().scale.height + 20;
		clientTransform.scale = clientScale;

		SetClientTransform(hWnd, clientTransform);

		SetTimer(hWnd, 1, 15, NULL);
		SetTimer(hWnd, 2, 1, NULL);
		SetTimer(hWnd, 3, 30, NULL);
		SetTimer(hWnd, 4, 90, NULL);

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
			pacman.PlayerMoveUpdate();
			pacman.EnemyMoveUpdate();
			break;

		case 3:
			pacman.PlayerGaspUpdate();
			break;

		case 4:
			pacman.EnemyStepUpdate();
			break;
		}
		return 0;

	case WM_PAINT:
		pacman.Paint(hWnd);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			pacman.SetInputDirection(Left);
			break;
		case VK_RIGHT:
			pacman.SetInputDirection(Right);
			break;
		case VK_UP:
			pacman.SetInputDirection(Up);
			break;
		case VK_DOWN:
			pacman.SetInputDirection(Down);
			break;
		}
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DEBUG:
			pacman.SetDebug(!pacman.GetDebug());
			break;
		}
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

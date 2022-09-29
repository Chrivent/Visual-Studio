#include<Windows.h>

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

#define W_BLACK RGB(0, 0, 0)
#define W_RED RGB(255, 0, 0)
#define W_GREEN RGB(0, 255, 0)
#define W_YELLOW RGB(255, 255, 0)
#define W_BLUE RGB(0, 0, 255)
#define W_PURPLE RGB(255, 0, 255)
#define W_SKYBLUE RGB(0, 255, 255)
#define W_WHITE RGB(255, 255, 255)
#define W_GRAY RGB(128, 128, 128)

#define FRAME 30

struct Position
{
	int x = 0;
	int y = 0;

	bool operator == (Position position)
	{
		if (x == position.x && y == position.y)
			return true;
		return false;
	}
	bool operator != (Position position)
	{
		if (*this == position)
			return false;
		return true;
	}
};

struct Scale
{
	int width = 0;
	int height = 0;

	bool operator == (Scale scale)
	{
		if (width == scale.width && height == scale.height)
			return true;
		return false;
	}
	bool operator != (Scale scale)
	{
		if (*this == scale)
			return false;
		return true;
	}
};

struct Transform
{
	Position position;
	Scale scale;

	void MoveLeft(int distance = 1)
	{
		position.x -= distance;
	}

	void MoveRight(int distance = 1)
	{
		position.x += distance;
	}

	void MoveUp(int distance = 1)
	{
		position.y -= distance;
	}

	void MoveDown(int distance = 1)
	{
		position.y += distance;
	}
};

struct Object
{
	Transform transform;

	Object(Transform transform)
	{
		this->transform = transform;
	}

	virtual void Draw(HDC hdc) = 0;
};

Transform GetClientTransform(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	return { { rect.left, rect.top }, { rect.right - rect.left, rect.bottom - rect.top } };
}

void DrawEllipseCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
{
	HBRUSH myBrush = CreateSolidBrush(faceColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

	Ellipse(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

class Ball : public Object
{
private:
	COLORREF color;
	int thickness;

public:
	Ball(Transform transform, int thickness) : Object(transform)
	{
		ResetColor();

		this->thickness = thickness;
	}

	void SetColor(COLORREF color)
	{
		this->color = color;
	}

	void ResetColor()
	{
		color = W_SKYBLUE;
	}

	void Draw(HDC hdc)
	{
		DrawEllipseCustom(hdc, transform, thickness, color, W_PURPLE);
	}
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HDC g_MemDC;
	HBITMAP g_hBitmap;
	HBITMAP g_hOld;

	static Ball ball({ { 100, 100 }, { 200, 200 } }, 5);
	static int speed = 40;
	static COLORREF color = W_RED;

	Position clientPosition;
	Scale clientScale;

	Position ballPosition;
	Scale ballScale;

	int widthMax;
	int heightMax;

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000 / FRAME, NULL);
		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		g_MemDC = CreateCompatibleDC(hdc);
		g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
		g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

		ball.Draw(hdc);

		SelectObject(g_MemDC, g_hOld);
		DeleteObject(g_hBitmap);
		DeleteDC(g_MemDC);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_KEYDOWN:;
		clientPosition = GetClientTransform(hWnd).position;
		clientScale = GetClientTransform(hWnd).scale;

		ballPosition = ball.transform.position;
		ballScale = ball.transform.scale;

		widthMax = clientPosition.x + clientScale.width - ballScale.width;
		heightMax = clientPosition.y + clientScale.height - ballScale.height;

		switch (wParam)
		{
		case VK_LEFT:
			if (clientPosition.x < ballPosition.x - speed)
				ball.transform.MoveLeft(speed);
			else
				ball.transform.position.x = clientPosition.x;
			break;

		case VK_RIGHT:
			if (clientPosition.x + clientScale.width > ballPosition.x + ballScale.width + speed)
				ball.transform.MoveRight(speed);
			else
				ball.transform.position.x = widthMax;
			break;

		case VK_UP:
			if (clientPosition.y < ballPosition.y - speed)
				ball.transform.MoveUp(speed);
			else
				ball.transform.position.y = clientPosition.y;
			break;

		case VK_DOWN:
			if (clientPosition.y + clientScale.height > ballPosition.y + ballScale.height + speed)
				ball.transform.MoveDown(speed);
			else
				ball.transform.position.y = heightMax;
			break;
		}

		ballPosition = ball.transform.position;

		if (ballPosition.x == clientPosition.x || ballPosition.x == widthMax || ballPosition.y == clientPosition.y || ballPosition.y == heightMax)
			ball.SetColor(color);
		else
			ball.ResetColor();

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
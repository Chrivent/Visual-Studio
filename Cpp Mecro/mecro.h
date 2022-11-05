#pragma once

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Gdiplus.lib")

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<crtdbg.h>
#include<tchar.h>
#include<locale.h>
#include<mmsystem.h>
#include<gdiplus.h>

#define C_BLACK 0x0000
#define C_DARK_BLUE 0x0001
#define C_GREEN 0x0002
#define C_BLUE_GREEN 0x0003
#define C_BLOOD 0x0004
#define C_PUPPLE 0x0005
#define C_GOLD 0x0006
#define C_ORIGINAL 0x0007
#define C_GRAY 0x0008
#define C_BLUE 0x0009
#define C_HIGH_GREEN 0x000a
#define C_SKY_BLUE 0x000b
#define C_RED 0x000c
#define C_PLUM 0x000d
#define C_YELLOW 0x000e

#define W_BLACK RGB(0, 0, 0)
#define W_RED RGB(255, 0, 0)
#define W_GREEN RGB(0, 255, 0)
#define W_YELLOW RGB(255, 255, 0)
#define W_BLUE RGB(0, 0, 255)
#define W_PURPLE RGB(255, 0, 255)
#define W_SKYBLUE RGB(0, 255, 255)
#define W_WHITE RGB(255, 255, 255)
#define W_GRAY RGB(128, 128, 128)

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ENTER 13
#define ESC 27
#define SPACE 32
#define BACKSPACE 8

#define FRAME 30

using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::list;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::fixed;
using std::setprecision;
using Gdiplus::GdiplusStartupInput;
using Gdiplus::Image;
using Gdiplus::Graphics;

struct Position
{
	int x = 0;
	int y = 0;

	Position operator + (Position position)
	{
		Position tmp;
		tmp.x = x + position.x;
		tmp.y = y + position.y;
		return tmp;
	}
	Position operator - (Position position)
	{
		Position tmp;
		tmp.x = x - position.x;
		tmp.y = y - position.y;
		return tmp;
	}
	Position operator * (Position position)
	{
		Position tmp;
		tmp.x = x * position.x;
		tmp.y = y * position.y;
		return tmp;
	}
	Position operator / (Position position)
	{
		Position tmp;
		tmp.x = x / position.x;
		tmp.y = y / position.y;
		return tmp;
	}
	Position operator % (Position position)
	{
		Position tmp;
		tmp.x = x % position.x;
		tmp.y = y % position.y;
		return tmp;
	}

	void operator += (Position position)
	{
		*this = *this + position;
	}
	void operator -= (Position position)
	{
		*this = *this - position;
	}
	void operator *= (Position position)
	{
		*this = *this * position;
	}
	void operator /= (Position position)
	{
		*this = *this / position;
	}
	void operator %= (Position position)
	{
		*this = *this % position;
	}

	void operator ++ ()
	{
		x++;
		y++;
	}
	void operator ++ (int)
	{
		++(*this);
	}

	void operator -- ()
	{
		x--;
		y--;
	}
	void operator -- (int)
	{
		--(*this);
	}

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

	bool operator > (Position position)
	{
		if (x > position.x && y > position.y)
			return true;
		return false;
	}
	bool operator >= (Position position)
	{
		if (*this > position || *this == position)
			return true;
		return false;
	}

	bool operator < (Position position)
	{
		if (x < position.x && y < position.y)
			return true;
		return false;
	}
	bool operator <= (Position position)
	{
		if (*this < position || *this == position)
			return true;
		return false;
	}
};

struct Move
{
	Position position;

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

struct Scale
{
	int width = 0;
	int height = 0;

	Scale operator + (Scale scale)
	{
		Scale tmp;
		tmp.width = width + scale.width;
		tmp.height = height + scale.height;
		return tmp;
	}
	Scale operator - (Scale scale)
	{
		Scale tmp;
		tmp.width = width - scale.width;
		tmp.height = height - scale.height;
		return tmp;
	}
	Scale operator * (Scale scale)
	{
		Scale tmp;
		tmp.width = width * scale.width;
		tmp.height = height * scale.height;
		return tmp;
	}
	Scale operator / (Scale scale)
	{
		Scale tmp;
		tmp.width = width / scale.width;
		tmp.height = height / scale.height;
		return tmp;
	}
	Scale operator % (Scale scale)
	{
		Scale tmp;
		tmp.width = width % scale.width;
		tmp.height = height % scale.height;
		return tmp;
	}

	void operator += (Scale scale)
	{
		*this = *this + scale;
	}
	void operator -= (Scale scale)
	{
		*this = *this - scale;
	}
	void operator *= (Scale scale)
	{
		*this = *this * scale;
	}
	void operator /= (Scale scale)
	{
		*this = *this / scale;
	}
	void operator %= (Scale scale)
	{
		*this = *this % scale;
	}

	void operator ++ ()
	{
		width++;
		height++;
	}
	void operator ++ (int)
	{
		++(*this);
	}

	void operator -- ()
	{
		width--;
		height--;
	}
	void operator -- (int)
	{
		--(*this);
	}

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

	bool operator > (Scale scale)
	{
		if (width > scale.width && height > scale.height)
			return true;
		return false;
	}
	bool operator >= (Scale scale)
	{
		if (*this > scale || *this == scale)
			return true;
		return false;
	}

	bool operator < (Scale scale)
	{
		if (width < scale.width && height < scale.height)
			return true;
		return false;
	}
	bool operator <= (Scale scale)
	{
		if (*this < scale || *this == scale)
			return true;
		return false;
	}
};

int RandNum(int min, int max)
{
	static bool tmp = false;

	if (tmp == false)
	{
		srand((unsigned int)time(NULL));

		tmp = true;
	}

	while (true)
	{
		int num = rand() % max;

		if (num >= min)
			return num;
	}
}

bool RandBool(int denominator, int numerator)
{
	int randNum = RandNum(0, denominator);

	if (randNum >= 0 && randNum <= numerator)
		return true;
	return false;
}

float Pi()
{
	return (float)atan(1) * 4;
}

SYSTEMTIME CurrentTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	return st;
}

float DiagonalLength(Scale scale)
{
	return (float)sqrt(pow(scale.width, 2) + pow(scale.height, 2));
}

float PositionAngle(Position position1, Position position2)
{
	Scale scale;
	float angle;

	if (position1.x <= position2.x)
	{
		scale.width = position2.x - position1.x;
		if (position1.y <= position2.y)
		{
			scale.height = position2.y - position1.y;
			angle = acos(scale.width / DiagonalLength(scale)) * (180 / Pi());
		}
		else
		{
			scale.height = position1.y - position2.y;
			angle = acos(scale.height / DiagonalLength(scale)) * (180 / Pi()) + 270;
		}
	}
	else
	{
		scale.width = position1.x - position2.x;
		if (position1.y <= position2.y)
		{
			scale.height = position2.y - position1.y;
			angle = acos(scale.height / DiagonalLength(scale)) * (180 / Pi()) + 90;
		}
		else
		{
			scale.height = position1.y - position2.y;
			angle = acos(scale.width / DiagonalLength(scale)) * (180 / Pi()) + 180;
		}
	}

	return angle;
}

Position AnglePosition(Position position, int length, float angle)
{
	return { int(position.x + length * cos(angle * Pi() / 180)), int(position.y + length * sin(angle * Pi() / 180)) };
}

namespace cMecro
{
	void Gotoxy(int x, int y)
	{
		COORD Pos = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	void SetScreenSize(int width, int height)
	{
		system(("mode con: lines=" + to_string(height) + " cols=" + to_string((width * 2) + 1)).c_str());
	}

	int Hit()
	{
		return _kbhit() ? _getch() : NULL;
	}

	void Print(string str, int color = C_ORIGINAL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << str;
	}

	void Print(char cha, int color = C_ORIGINAL)
	{
		Print(string(1, cha), color);
	}

	void Print(int num, int color = C_ORIGINAL)
	{
		Print(to_string(num), color);
	}

	void PrintLine(string str, int color = C_ORIGINAL)
	{
		Print(str, color);
		cout << endl;
	}

	void PrintLine(char cha, int color = C_ORIGINAL)
	{
		Print(cha, color);
		cout << endl;
	}

	void PrintLine(int num, int color = C_ORIGINAL)
	{
		Print(num, color);
		cout << endl;
	}

	void Scan(string& str, int color = C_ORIGINAL)
	{
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					cout << endl;
					return;
				}
				else if (input == BACKSPACE)
				{
					if (str.length() > 0)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						str.pop_back();
					}
				}
				else
				{
					Print(input, color);
					str.push_back(input);
				}
			}
		}
	}

	void Scan(char& cha, int color = C_ORIGINAL)
	{
		cha = NULL;
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					cout << endl;
					return;
				}
				else if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || (input >= '0' && input <= '9'))
				{
					if (cha != NULL)
						Print("\b");
					Print(input, color);
					cha = input;
				}
				else
				{
					if (cha != NULL)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						cha = NULL;
					}
				}
			}
		}
	}

	void Scan(int& num, int color = C_ORIGINAL)
	{
		string str;
		while (true)
		{
			char input = Hit();
			if (input)
			{
				if (input == ENTER)
				{
					num = atoi(str.c_str());
					cout << endl;
					return;
				}
				else if (input == BACKSPACE)
				{
					if (str.length() > 0)
					{
						Print("\b");
						Print(" ");
						Print("\b");
						str.pop_back();
					}
				}
				else if (input >= '0' && input <= '9')
				{
					Print(input, color);
					str.push_back(input);
				}
			}
		}
	}

	string InputStr(int color = C_ORIGINAL)
	{
		string str;
		Scan(str, color);
		return str;
	}

	char InputCha(int color = C_ORIGINAL)
	{
		char cha;
		Scan(cha, color);
		return cha;
	}

	int InputNum(int color = C_ORIGINAL)
	{
		int num;
		Scan(num, color);
		return num;
	}

	struct Transform : public Move
	{
		Scale scale;

		bool operator == (Transform transform)
		{
			if (position == transform.position && scale == transform.scale)
				return true;
			return false;
		}
		bool operator != (Transform transform)
		{
			if (*this == transform)
				return false;
			return true;
		}
	};

	struct Object : public Move
	{
		virtual void Draw() = 0;
	};

	struct Material
	{
		string texture;
		int color;

		bool operator == (Material material)
		{
			if (texture == material.texture && color == material.color)
				return true;
			return false;
		}
		bool operator != (Material material)
		{
			if (*this == material)
				return false;
			return true;
		}
	};

	void _DrawText(int x, int y, string text, int color = C_ORIGINAL)
	{
		Gotoxy(x * 2, y);
		Print(text, color);
	}
	void DrawTextMiddle(int x, int y, string text, int color = C_ORIGINAL)
	{
		_DrawText(x - (int)text.size() / 4, y, text, color);
	}
	void DrawPoint(int x, int y, string texture, int color = C_ORIGINAL)
	{
		Gotoxy(x * 2, y);
		Print(texture, color);
	}
	void DrawWidthLine(int x, int y, int width, string texture, int color = C_ORIGINAL)
	{
		for (int i = 0; i < width; i++)
			DrawPoint(x + i, y, texture, color);
	}
	void DrawHeightLine(int x, int y, int height, string texture, int color = C_ORIGINAL)
	{
		for (int i = 0; i < height; i++)
			DrawPoint(x, y + i, texture, color);
	}
	void DrawRectangle(int x, int y, int width, int height, string texture, int color = C_ORIGINAL)
	{
		for (int i = 0; i < height; i++)
			DrawWidthLine(x, y + i, width, texture, color);
	}
	void DrawEmptyRectangle(int x, int y, int width, int height, string texture, int color = C_ORIGINAL)
	{
		DrawWidthLine(x, y, width, texture, color);
		DrawHeightLine(x, y + 1, height - 2, texture, color);
		DrawHeightLine(x + width - 1, y + 1, height - 2, texture, color);
		DrawWidthLine(x, y + height - 1, width, texture, color);
	}
	void DrawBox(int x, int y, int width, int height, int color = C_ORIGINAL)
	{
		DrawPoint(x, y, "�� ", color);
		DrawWidthLine(x + 1, y, width - 2, "�� ", color);
		DrawPoint(x + width - 1, y, "�� ", color);
		DrawHeightLine(x, y + 1, height - 2, "�� ", color);
		DrawHeightLine(x + width - 1, y + 1, height - 2, "�� ", color);
		DrawPoint(x, y + height - 1, "�� ", color);
		DrawWidthLine(x + 1, y + height - 1, width - 2, "�� ", color);
		DrawPoint(x + width - 1, y + height - 1, "�� ", color);
	}
	void DrawGrid(int x, int y, int width, int height, int color = C_ORIGINAL)
	{
		DrawPoint(x, y, "�� ", color);
		DrawWidthLine(x + 1, y, width - 2, "�� ", color);
		DrawPoint(x + width - 1, y, "�� ", color);
		DrawHeightLine(x, y + 1, height - 2, "�� ", color);
		DrawRectangle(x + 1, y + 1, width - 2, height - 2, "�� ", color);
		DrawHeightLine(x + width - 1, y + 1, height - 2, "�� ", color);
		DrawPoint(x, y + height - 1, "�� ", color);
		DrawWidthLine(x + 1, y + height - 1, width - 2, "�� ", color);
		DrawPoint(x + width - 1, y + height - 1, "�� ", color);
	}

	template <typename Type>
	void DrawObject(Type* object)
	{
		if (object != nullptr)
			object->Draw();
	}

	template <typename Type>
	void DrawObject(vector<Type*> object)
	{
		for (int i = 0; i < object.size(); i++)
			DrawObject(object[i]);
	}

	class Game
	{
	protected:
		int scene;

		virtual void Draw() = 0;
		virtual void Start() = 0;
		virtual bool Update() = 0;

	public:
		Game()
		{
			scene = 0;
		}

		void Play()
		{
			system("cls");

			cout << "Loading...";

			Sleep(4000);

			Start();

			while (Update());

			scene = 0;

			system("cls");

			cout << "Thank you for playing my game";

			Sleep(4000);
		}
	};
}

namespace wMecro
{
	struct Transform : public Move
	{
		Scale scale;

		bool operator == (Transform transform)
		{
			if (position == transform.position && scale == transform.scale)
				return true;
			return false;
		}
		bool operator != (Transform transform)
		{
			if (*this == transform)
				return false;
			return true;
		}
	};

	struct Object
	{
		Transform transform;

		virtual void Draw(HDC hdc) = 0;
	};

	Position GetMousePosition(LPARAM lParam)
	{
		return { LOWORD(lParam), HIWORD(lParam) };
	}

	Scale BitmapScale(HDC hdc, LPCWSTR fileName)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		BITMAP bitmap;
		GetObject(myBitmap, sizeof(BITMAP), (LPVOID)&bitmap);

		Scale scale;
		scale.width = (int)bitmap.bmWidth;
		scale.height = (int)bitmap.bmHeight;

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);

		return scale;
	}

	Scale ScreenScale()
	{
		return { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	}

	void SetWindowTransform(HWND hWnd, Transform transform)
	{
		SetWindowPos(hWnd, NULL, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, 0);
	}

	void SetClientTransform(HWND hWnd, Transform transform)
	{
		SetWindowPos(hWnd, NULL, transform.position.x, transform.position.y, transform.scale.width + GetSystemMetrics(SM_CXFRAME) * 4, transform.scale.height + GetSystemMetrics(SM_CYFRAME) * 4 + GetSystemMetrics(SM_CYCAPTION), 0);
	}

	Transform GetWindowTransform(HWND hWnd)
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);

		Transform tmp;
		tmp.position = { rect.left, rect.top };
		tmp.scale = { rect.right - rect.left, rect.bottom - rect.top };

		return tmp;
	}

	Transform GetClientTransform(HWND hWnd)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		Transform tmp;
		tmp.position = { rect.left, rect.top };
		tmp.scale = { rect.right - rect.left, rect.bottom - rect.top };

		return tmp;
	}

	bool CheckPositionIsInTransform(Transform transform, Position position)
	{
		RECT rect =
		{
		transform.position.x,
		transform.position.y,
		transform.position.x + transform.scale.width,
		transform.position.y + transform.scale.height
		};

		POINT point =
		{
		point.x = position.x,
		point.y = position.y
		};

		if (PtInRect(&rect, point))
			return true;
		return false;
	}

	bool CheckTransformIsIntersect(Transform transform1, Transform transform2)
	{
		RECT tmp;

		RECT rect1 =
		{
		transform1.position.x,
		transform1.position.y,
		transform1.position.x + transform1.scale.width,
		transform1.position.y + transform1.scale.height
		};

		RECT rect2 =
		{
		transform2.position.x,
		transform2.position.y,
		transform2.position.x + transform2.scale.width,
		transform2.position.y + transform2.scale.height
		};

		if (IntersectRect(&tmp, &rect1, &rect2))
			return true;
		return false;
	}

	void DrawLine(HDC hdc, Position position1, Position position2, int thickness, COLORREF color = W_BLACK)
	{
		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		MoveToEx(hdc, position1.x, position1.y, NULL);
		LineTo(hdc, position2.x, position2.y);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangle(HDC hdc, Transform transform, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(color);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, 1, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangleEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawRectangleCustom(HDC hdc, Transform transform, int thickness, COLORREF faceColor, COLORREF edgeColor)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Rectangle(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawPolygon(HDC hdc, Transform transform, int vertexCount, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(color);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, 1, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Position centerPosition = { transform.position.x + transform.scale.width / 2, transform.position.y + transform.scale.height / 2 };

		POINT* vertexs = new POINT[vertexCount];

		for (int i = 0; i < vertexCount; i++)
		{
			Position tmp = AnglePosition(centerPosition, (transform.scale.width + transform.scale.height) / 4, 360.0f / vertexCount * i - 90);
			POINT point = { tmp.x, tmp.y };
			vertexs[i] = point;
		}

		Polygon(hdc, vertexs, vertexCount);

		delete[] vertexs;
		vertexs = nullptr;

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawPolygonEmpty(HDC hdc, Transform transform, int vertexCount, int thickness, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Position centerPosition = { transform.position.x + transform.scale.width / 2, transform.position.y + transform.scale.height / 2 };

		POINT* vertexs = new POINT[vertexCount];

		for (int i = 0; i < vertexCount; i++)
		{
			Position tmp = AnglePosition(centerPosition, (transform.scale.width + transform.scale.height) / 4, 360.0f / vertexCount * i - 90);
			POINT point = { tmp.x, tmp.y };
			vertexs[i] = point;
		}

		Polygon(hdc, vertexs, vertexCount);

		delete[] vertexs;
		vertexs = nullptr;

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawPolygonCustom(HDC hdc, Transform transform, int vertexCount, int thickness, COLORREF faceColor, COLORREF edgeColor = W_BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(faceColor);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, edgeColor);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Position centerPosition = { transform.position.x + transform.scale.width / 2, transform.position.y + transform.scale.height / 2 };

		POINT* vertexs = new POINT[vertexCount];

		for (int i = 0; i < vertexCount; i++)
		{
			Position tmp = AnglePosition(centerPosition, (transform.scale.width + transform.scale.height) / 4, 360.0f / vertexCount * i - 90);
			POINT point = { tmp.x, tmp.y };
			vertexs[i] = point;
		}

		Polygon(hdc, vertexs, vertexCount);

		delete[] vertexs;
		vertexs = nullptr;

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawEllipse(HDC hdc, Transform transform, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = CreateSolidBrush(color);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, 1, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x, transform.position.y, transform.position.x + transform.scale.width, transform.position.y + transform.scale.height);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
	}

	void DrawEllipseEmpty(HDC hdc, Transform transform, int thickness, COLORREF color = W_BLACK)
	{
		HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		HPEN myPen = CreatePen(PS_SOLID, thickness, color);
		HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

		Ellipse(hdc, transform.position.x + thickness / 2, transform.position.y + thickness / 2, transform.position.x + transform.scale.width - thickness / 2, transform.position.y + transform.scale.height - thickness / 2);

		SelectObject(hdc, oldBrush);
		DeleteObject(myBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(myPen);
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

	void DrawTextOut(HDC hdc, Transform transform, LPCWSTR text, COLORREF color = W_BLACK)
	{
		int width = transform.scale.width / lstrlen(text);

		HFONT myFont = CreateFont(transform.scale.height, width, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("�ü�"));
		HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

		SetTextColor(hdc, color);
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, transform.position.x, transform.position.y, text, lstrlen(text));

		SelectObject(hdc, oldFont);
		DeleteObject(myFont);
	}

	void DrawBitmap(HDC hdc, Transform transform, LPCWSTR fileName)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		Scale bitmapScale = BitmapScale(hdc, fileName);
		StretchBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, 0, 0, bitmapScale.width, bitmapScale.height, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void DrawBitmapTransparent(HDC hdc, Transform transform, LPCWSTR fileName, COLORREF color = W_PURPLE)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		Scale bitmapScale = BitmapScale(hdc, fileName);
		TransparentBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, 0, 0, bitmapScale.width, bitmapScale.height, color);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void DrawBitmapPart(HDC hdc, Transform transform, LPCWSTR fileName, int widthCell, int heightCell, int index)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		if (index >= widthCell * heightCell)
			index = widthCell * heightCell - 1;

		Scale bitmapScale = BitmapScale(hdc, fileName);
		StretchBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, bitmapScale.width / widthCell * (index % widthCell), bitmapScale.height / heightCell * (index / heightCell), bitmapScale.width / widthCell, bitmapScale.height / heightCell, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void DrawBitmapPartTransparent(HDC hdc, Transform transform, LPCWSTR fileName, int widthCell, int heightCell, int index, COLORREF color = W_PURPLE)
	{
		HDC MemDC = CreateCompatibleDC(hdc);

		HBITMAP myBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(MemDC, myBitmap);

		if (index >= widthCell * heightCell)
			index = widthCell * heightCell - 1;

		Scale bitmapScale = BitmapScale(hdc, fileName);
		TransparentBlt(hdc, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height, MemDC, bitmapScale.width / widthCell * (index % widthCell), bitmapScale.height / heightCell * (index / heightCell), bitmapScale.width / widthCell, bitmapScale.height / heightCell, color);

		SelectObject(MemDC, oldBitmap);
		DeleteObject(myBitmap);
		DeleteDC(MemDC);
	}

	void DrawGdi(HDC hdc, Transform transform, LPCWSTR fileName)
	{
		ULONG_PTR gdiplusToken;
		GdiplusStartupInput gdiplusStartupInput;

		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		Image* image = Image::FromFile(fileName);
		Graphics g(hdc);

		g.DrawImage(image, transform.position.x, transform.position.y, transform.scale.width, transform.scale.height);

		delete image;
		image = nullptr;
	}

	template <typename Type>
	void DrawObject(HDC hdc, Type* object)
	{
		if (object != nullptr)
			object->Draw(hdc);
	}

	template <typename Type>
	void DrawObject(HDC hdc, vector<Type*> object)
	{
		for (int i = 0; i < object.size(); i++)
			DrawObject(hdc, object[i]);
	}

	class Game
	{
	protected:
		int scene;

		virtual void Draw(HDC hdc) = 0;

	public:
		Game()
		{
			scene = 0;
		}

		void Paint(HWND hWnd)
		{
			HDC hdc;
			PAINTSTRUCT ps;

			HDC g_MemDC;
			HBITMAP g_hBitmap;
			HBITMAP g_hOld;

			hdc = BeginPaint(hWnd, &ps);

			g_MemDC = CreateCompatibleDC(hdc);
			g_hBitmap = CreateCompatibleBitmap(hdc, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height);
			g_hOld = (HBITMAP)SelectObject(g_MemDC, g_hBitmap);

			DrawRectangle(g_MemDC, GetClientTransform(hWnd), W_WHITE);

			Draw(g_MemDC);

			BitBlt(hdc, 0, 0, GetClientTransform(hWnd).scale.width, GetClientTransform(hWnd).scale.height, g_MemDC, 0, 0, SRCCOPY);

			SelectObject(g_MemDC, g_hOld);
			DeleteObject(g_hBitmap);
			DeleteDC(g_MemDC);

			EndPaint(hWnd, &ps);
		}
	};
}

template <typename Type>
Type* GetObjectByPosition(Type* object, Position position)
{
	if (object != nullptr && object->position == position)
		return object;
	return nullptr;
}

template <typename Type>
Type* GetObjectByPosition(vector<Type*> object, Position position)
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i] != nullptr && object[i]->position == position)
			return object[i];
	}
	return nullptr;
}

template <typename Type>
void Delete(Type*& type)
{
	if (type != nullptr)
	{
		delete type;
		type = nullptr;
	}
}

template <typename Type>
void Delete(vector<Type*>& type)
{
	for (int i = 0; i < type.size(); i++)
		Delete(type[i]);
}

class Clock
{
private:
	int _clock;
	int time;

public:
	Clock()
	{
		_clock = clock();
		time = 1000;
	}

	void SetTime(int time)
	{
		this->time = time;
	}

	bool Alarm()
	{
		int tmp = clock();

		if (tmp - _clock >= time)
		{
			_clock = tmp;

			return true;
		}

		return false;
	}

	int GetTime()
	{
		return time;
	}
};

class StopWatch
{
private:
	Clock* _clock;
	int time;

public:
	StopWatch()
	{
		_clock = nullptr;
		time = 1000;
	}

	void SetTime(int time)
	{
		this->time = time;
	}

	void Start()
	{
		if (_clock != nullptr)
			Delete(_clock);

		_clock = new Clock;
		_clock->SetTime(time);
	}

	bool Stop()
	{
		if (_clock != nullptr && _clock->Alarm())
		{
			Delete(_clock);

			return true;
		}

		return false;
	}

	int GetTime()
	{
		return time;
	}

	~StopWatch()
	{
		if (_clock != nullptr)
			Delete(_clock);
	}
};
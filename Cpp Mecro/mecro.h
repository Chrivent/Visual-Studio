#pragma once
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib, "winmm.lib")

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
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<list>
#include<vector>

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

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ENTER 13
#define ESC 27
#define SPACE 32
#define BACKSPACE 8

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

struct Position
{
	int x;
	int y;

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

struct Scale
{
	int width;
	int height;

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
	static bool tmp;

	if (tmp != true)
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
	int randNum = RandNum(1, denominator);

	if (randNum >= 1 && randNum <= numerator)
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

Position AnglePosition(Position position, int length, int angle)
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
		Object(Position position)
		{
			this->position = position;
		}

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
		DrawPoint(x, y, "¦£ ", color);
		DrawWidthLine(x + 1, y, width - 2, "¦¡ ", color);
		DrawPoint(x + width - 1, y, "¦¤ ", color);
		DrawHeightLine(x, y + 1, height - 2, "¦¢ ", color);
		DrawHeightLine(x + width - 1, y + 1, height - 2, "¦¢ ", color);
		DrawPoint(x, y + height - 1, "¦¦ ", color);
		DrawWidthLine(x + 1, y + height - 1, width - 2, "¦¡ ", color);
		DrawPoint(x + width - 1, y + height - 1, "¦¥ ", color);
	}
	void DrawGrid(int x, int y, int width, int height, int color = C_ORIGINAL)
	{
		DrawPoint(x, y, "¦£ ", color);
		DrawWidthLine(x + 1, y, width - 2, "¦¨ ", color);
		DrawPoint(x + width - 1, y, "¦¤ ", color);
		DrawHeightLine(x, y + 1, height - 2, "¦§ ", color);
		DrawRectangle(x + 1, y + 1, width - 2, height - 2, "¦« ", color);
		DrawHeightLine(x + width - 1, y + 1, height - 2, "¦© ", color);
		DrawPoint(x, y + height - 1, "¦¦ ", color);
		DrawWidthLine(x + 1, y + height - 1, width - 2, "¦ª ", color);
		DrawPoint(x + width - 1, y + height - 1, "¦¥ ", color);
	}

	template <typename Type>
	void DrawObject(Type* object)
	{
		if (object != NULL)
			object->Draw();
	}

	template <typename Type>
	void DrawObject(vector<Type*> object)
	{
		for (int i = 0; i < object.size(); i++)
			DrawObject(object[i]);
	}

	template <typename Type>
	Type* GetObjectByPosition(Type* object, Position position)
	{
		if (object != NULL && object->position == position)
			return object;
		return NULL;
	}

	template <typename Type>
	Type* GetObjectByPosition(vector<Type*> object, Position position)
	{
		for (int i = 0; i < object.size(); i++)
		{
			if (GetObjectByPosition(object[i], position))
				return object[i];
		}
		return NULL;
	}
}

namespace wMecro
{
	struct Transform
	{
		Position position;
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

		return { { rect.left, rect.top }, { rect.right - rect.left, rect.bottom - rect.top } };
	}

	Transform GetClientTransform(HWND hWnd)
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		return { { rect.left, rect.top }, { rect.right - rect.left, rect.bottom - rect.top } };
	}

	bool CheckPositionIsInTransform(Transform transform, Position position)
	{
		RECT rect;
		rect.left = transform.position.x;
		rect.top = transform.position.y;
		rect.right = transform.position.x + transform.scale.width;
		rect.bottom = transform.position.y + transform.scale.height;

		POINT point;
		point.x = position.x;
		point.y = position.y;

		if (PtInRect(&rect, point))
			return true;
		return false;
	}

	bool CheckTransformIsIntersect(Transform transform1, Transform transform2)
	{
		RECT tmp, rect1, rect2;

		rect1.left = transform1.position.x;
		rect1.top = transform1.position.y;
		rect1.right = transform1.position.x + transform1.scale.width;
		rect1.bottom = transform1.position.y + transform1.scale.height;

		rect2.left = transform2.position.x;
		rect2.top = transform2.position.y;
		rect2.right = transform2.position.x + transform2.scale.width;
		rect2.bottom = transform2.position.y + transform2.scale.height;

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

		HFONT myFont = CreateFont(transform.scale.height, width, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("±Ã¼­"));
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

	template <typename Type>
	void DrawObject(HDC hdc, Type* object)
	{
		if (object != NULL)
			object->Draw(hdc);
	}

	template <typename Type>
	void DrawObject(HDC hdc, vector<Type*> object)
	{
		for (int i = 0; i < object.size(); i++)
			DrawObject(hdc, object[i]);
	}
}

template <typename Type>
void Delete(Type*& type)
{
	if (type != NULL)
	{
		delete type;
		type = NULL;
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
	int m_clock;
	int m_time;

public:
	Clock() { m_clock = clock(); m_time = 1000; }

	void SetTime(int time) { m_time = time; }
	bool Alarm()
	{
		int tmp = clock();
		if (tmp - m_clock >= m_time)
		{
			m_clock = tmp;
			return true;
		}
		return false;
	}
	int GetTime() { return m_time; }
};

class StopWatch
{
private:
	Clock* m_clock;
	int m_time;

public:
	StopWatch() { m_clock = NULL; m_time = 1000; }

	void SetTime(int time) { m_time = time; }
	void Start()
	{
		if (m_clock != NULL)
			Delete(m_clock);
		m_clock = new Clock;
		m_clock->SetTime(m_time);
	}
	bool Stop()
	{
		if (m_clock != NULL && m_clock->Alarm())
		{
			Delete(m_clock);
			return true;
		}
		return false;
	}
	int GetTime() { return m_time; }

	~StopWatch()
	{
		if (m_clock != NULL)
			Delete(m_clock);
	}
};

class Scene
{
public:
	virtual void Draw() = 0;
};

class Game
{
public:
	void Play()
	{
		while (Update());
	}

	virtual void Draw() = 0;
	virtual bool Update() = 0;
};
#include "mecro.h"

bool Position::operator == (Position position)
{
	if (x == position.x && y == position.y)
		return true;

	return false;
}

bool Position::operator != (Position position)
{
	if (*this == position)
		return false;

	return true;
}

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

void Print(string str, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << str;
}

void _DrawText(int x, int y, string text, int color)
{
	Gotoxy(x * 2, y);
	Print(text, color);
}

void DrawTextMiddle(int x, int y, string text, int color)
{
	_DrawText(x - (int)text.size() / 4, y, text, color);
}

void DrawPoint(int x, int y, string texture, int color)
{
	Gotoxy(x * 2, y);
	Print(texture, color);
}

void DrawWidthLine(int x, int y, int width, string texture, int color)
{
	for (int i = 0; i < width; i++)
		DrawPoint(x + i, y, texture, color);
}

void DrawHeightLine(int x, int y, int height, string texture, int color)
{
	for (int i = 0; i < height; i++)
		DrawPoint(x, y + i, texture, color);
}

void DrawEmptyRectangle(int x, int y, int width, int height, string texture, int color)
{
	DrawWidthLine(x, y, width, texture, color);
	DrawHeightLine(x, y + 1, height - 2, texture, color);
	DrawHeightLine(x + width - 1, y + 1, height - 2, texture, color);
	DrawWidthLine(x, y + height - 1, width, texture, color);
}

void DrawBox(int x, int y, int width, int height, int color)
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

Game::Game()
{
	scene = 0;
}

void Game::Play()
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

Clock::Clock()
{
	_clock = clock();
	time = 1000;
}

void Clock::SetTime(int time)
{
	this->time = time;
}

bool Clock::Alarm()
{
	int tmp = clock();

	if (tmp - _clock >= time)
	{
		_clock = tmp;

		return true;
	}

	return false;
}

int Clock::GetTime()
{
	return time;
}
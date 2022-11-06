#pragma once

#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>

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

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ENTER 13
#define ESC 27

using std::string;
using std::cout;
using std::to_string;

struct Position
{
	int x = 0;
	int y = 0;

	bool operator == (Position position);
	bool operator != (Position position);
};

struct Object
{
	Position position;

	virtual void Draw() = 0;
};

int RandNum(int min, int max);
void Gotoxy(int x, int y);
void SetScreenSize(int width, int height);
int Hit();
void Print(string str, int color = C_ORIGINAL);
void _DrawText(int x, int y, string text, int color = C_ORIGINAL);
void DrawTextMiddle(int x, int y, string text, int color = C_ORIGINAL);
void DrawPoint(int x, int y, string texture, int color = C_ORIGINAL);
void DrawWidthLine(int x, int y, int width, string texture, int color = C_ORIGINAL);
void DrawHeightLine(int x, int y, int height, string texture, int color = C_ORIGINAL);
void DrawEmptyRectangle(int x, int y, int width, int height, string texture, int color = C_ORIGINAL);
void DrawBox(int x, int y, int width, int height, int color = C_ORIGINAL);

class Game
{
protected:
	int scene;

	virtual void Draw() = 0;
	virtual void Start() = 0;
	virtual bool Update() = 0;

public:
	Game();

	void Play();
};

class Clock
{
private:
	int _clock;
	int time;

public:
	Clock();

	void SetTime(int time);
	bool Alarm();
	int GetTime();
};
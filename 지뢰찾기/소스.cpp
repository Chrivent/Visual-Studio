#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>

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

#define SPACE 32

using namespace std;

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

void DrawPoint(int x, int y, string texture, int color = C_ORIGINAL)
{
	Gotoxy(x * 2, y);
	Print(texture, color);
}

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

struct Object
{
	Position position;

	virtual void Draw() = 0;
};

class Bomb : public Object
{
public:
	void Draw()
	{
		DrawPoint(position.x, position.y, "¡Ø", C_BLOOD);
	}
};

class Sell : public Object
{
private:
	int bombCount;

public:
	Sell()
	{
		bombCount = 0;
	}

	void SetBombCount(int bombCount)
	{
		this->bombCount = bombCount;
	}

	int GetBombCount()
	{
		return bombCount;
	}

	void Draw()
	{
		switch (bombCount)
		{
		case 0:
			DrawPoint(position.x, position.y, "  ");
			break;

		case 1:
			DrawPoint(position.x, position.y, "£±", C_SKY_BLUE);
			break;

		case 2:
			DrawPoint(position.x, position.y, "£²", C_HIGH_GREEN);
			break;

		case 3:
			DrawPoint(position.x, position.y, "£³", C_RED);
			break;

		case 4:
			DrawPoint(position.x, position.y, "£´", C_BLUE);
			break;

		case 5:
			DrawPoint(position.x, position.y, "£µ", C_GOLD);
			break;

		case 6:
			DrawPoint(position.x, position.y, "£¶", C_GREEN);
			break;

		case 7:
			DrawPoint(position.x, position.y, "£·", C_PUPPLE);
			break;

		case 8:
			DrawPoint(position.x, position.y, "£¸", C_YELLOW);
			break;
		}
	}
};

class Tile : public Object
{
private:
	bool open;

public:
	Tile()
	{
		open = false;
	}

	bool CheckOpen()
	{
		return open;
	}

	void Open()
	{
		open = true;
	}

	void Draw()
	{
		if (open == false)
			DrawPoint(position.x, position.y, "¡á", C_GRAY);
	}
};

class Cursor : public Object
{
public:
	void Draw()
	{
		DrawPoint(position.x, position.y, "¢Ã");
	}
};

class Map
{
private:
	int width;
	int height;
	int bombCount;

	Sell** sells;
	Bomb* bombs;
	Tile** tiles;
	Cursor cursor;

public:
	Map(int width, int height, int bombCount)
	{
		this->width = width;
		this->height = height;
		this->bombCount = bombCount;

		SellArrangement();
		BombArrangement();
		TileArrangement();
		CursorArrangment();
	}

	void SellArrangement()
	{
		sells = new Sell * [height];

		for (int y = 0; y < height; y++)
			sells[y] = new Sell[width];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				sells[y][x].position = { x, y };
		}
	}

	void BombArrangement()
	{
		bombs = new Bomb[bombCount];

		for (int i = 0; i < bombCount; i++)
		{
			bool relocation = true;

			while (relocation)
			{
				relocation = false;

				bombs[i].position = { RandNum(0, width), RandNum(0, height) };

				for (int j = 0; j < i; j++)
				{
					if (bombs[j].position == bombs[i].position)
						relocation = true;
				}
			}
		}
	}

	void TileArrangement()
	{
		tiles = new Tile * [height];

		for (int y = 0; y < height; y++)
			tiles[y] = new Tile[width];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				tiles[y][x].position = { x, y };
		}
	}

	void CursorArrangment()
	{
		cursor.position.x = width / 2;
		cursor.position.y = height / 2;
	}

	bool CheckBombByPosition(Position position)
	{
		for (int i = 0; i < bombCount; i++)
		{
			if (bombs[i].position == position)
				return true;
		}

		return false;
	}

	void CountBomb()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int bombCount = 0;

				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i != 0 || j != 0)
						{
							if (CheckBombByPosition({ x + i, y + j }))
								bombCount++;
						}
					}
				}

				sells[y][x].SetBombCount(bombCount);
			}
		}
	}

	void OpenTiles(Position position)
	{
		if (tiles[position.y][position.x].CheckOpen())
			return;

		tiles[position.y][position.x].Open();

		if (sells[position.y][position.x].GetBombCount() != 0)
			return;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i != 0 || j != 0)
				{
					int x = position.x + j;
					int y = position.y + i;

					if (x >= 0 && x < width && y >= 0 && y < height)
						OpenTiles({ x, y });
				}
			}
		}
	}

	void OpenWholeTiles()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				tiles[y][x].Open();
		}
	}

	void Draw()
	{
		system("cls");

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (!CheckBombByPosition({ x, y }) && tiles[y][x].CheckOpen() == true)
					sells[y][x].Draw();
			}
		}

		for (int i = 0; i < bombCount; i++)
		{
			if (tiles[bombs[i].position.y][bombs[i].position.x].CheckOpen() == true)
				bombs[i].Draw();
		}

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
				tiles[y][x].Draw();
		}

		cursor.Draw();

		Gotoxy(0, height);
		cout << "";
	}

	void Start()
	{
		CountBomb();

		Draw();
	}

	bool Update()
	{
		switch (Hit())
		{
		case LEFT:
			if (cursor.position.x > 0)
			{
				cursor.position.x--;
				Draw();
			}
			break;

		case RIGHT:
			if (cursor.position.x < width - 1)
			{
				cursor.position.x++;
				Draw();
			}
			break;

		case UP:
			if (cursor.position.y > 0)
			{
				cursor.position.y--;
				Draw();
			}
			break;

		case DOWN:
			if (cursor.position.y < height - 1)
			{
				cursor.position.y++;
				Draw();
			}
			break;

		case SPACE:
			if (CheckBombByPosition(cursor.position) == false)
				OpenTiles(cursor.position);
			else
			{
				OpenWholeTiles();
				Draw();
				return false;
			}
			Draw();
			break;
		}

		return true;
	}

	~Map()
	{
		for (int y = 0; y < height; y++)
			delete[] sells[y];

		delete[] sells;

		delete[] bombs;

		for (int y = 0; y < height; y++)
			delete[] tiles[y];

		delete[] tiles;
	}
};

int main()
{
	int width, height, bombCount;

	cout << "°¡·Î : " << endl;
	cin >> width;

	cout << "¼¼·Î : " << endl;
	cin >> height;

	cout << "ÆøÅº °¹¼ö : " << endl;
	cin >> bombCount;

	Map map(width, height, bombCount);

	height += 10;
	width += 10;

	SetScreenSize(width, height);

	map.Start();

	while (map.Update());

	Gotoxy(0, height);

	return 0;
}
#include "C:\Users\USER\Desktop\Visual-Studio\Cpp Mecro\mecro.h"

using namespace cMecro;

#define WIDTH 18
#define HEIGHT 12
#define LEVEL 100

class Fall : public Object
{
protected:
	bool falling;

public:
	Fall(Position position) : Object(position)
	{
		falling = false;
	}

	bool CheckFalling()
	{
		return falling;
	}

	void SetFalling(bool falling)
	{
		this->falling = falling;
	}
};

class Wall : public Object
{
public:
	Wall(Position position) : Object(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¡á", C_GOLD);
	}
};

class Stone : public Object
{
public:
	Stone(Position position) : Object(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢Ì", C_GRAY);
	}
};

class Sand : public Object
{
public:
	Sand(Position position) : Object(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢Æ ", C_YELLOW);
	}
};

class Door : public Object
{
public:
	Door(Position position) : Object(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢È", C_GRAY);
	}
};

class Key : public Fall
{
public:
	Key(Position position) : Fall(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢Ò", C_YELLOW);
	}
};

class Marble : public Fall
{
public:
	Marble(Position position) : Fall(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¡Ý", C_SKY_BLUE);
	}
};

class Rock : public Fall
{
public:
	Rock(Position position) : Fall(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¡Ü", C_GRAY);
	}
};

class Portal : public Object
{
protected:
	int marbleCount;

public:
	Portal(Position position, int marbleCount) : Object(position)
	{
		this->marbleCount = marbleCount;
	}

	void InsertMarble(Marble*& marble)
	{
		Delete(marble);

		marbleCount--;
	}

	bool CheckFull()
	{
		if (marbleCount == 0)
			return true;

		return false;
	}

	void Draw()
	{
		DrawPoint(position.x, position.y - 1, (marbleCount != 0) ? "  " : "¡é", C_SKY_BLUE);
		DrawPoint(position.x, position.y, "¢Ã", (marbleCount != 0) ? C_BLUE : C_HIGH_GREEN);
	}
};

class Bug : public Object
{
protected:
	int direction;

public:
	Bug(Position position) : Object(position)
	{
		direction = UP;
	}

	void Move()
	{
		switch (direction)
		{
		case LEFT:
			MoveLeft();
			break;

		case RIGHT:
			MoveRight();
			break;

		case UP:
			MoveUp();
			break;

		case DOWN:
			MoveDown();
			break;
		}
	}

	int GetDirection()
	{
		return direction;
	}

	void RotateDirection()
	{
		if (direction == UP)
			direction = RIGHT;
		else if (direction == RIGHT)
			direction = DOWN;
		else if (direction == DOWN)
			direction = LEFT;
		else
			direction = UP;
	}

	void RotateDirectionRevert()
	{
		if (direction == UP)
			direction = LEFT;
		else if (direction == LEFT)
			direction = DOWN;
		else if (direction == DOWN)
			direction = RIGHT;
		else
			direction = UP;
	}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢Ï", C_GREEN);
	}
};

class Player : public Object
{
public:
	Player(Position position) : Object(position) {}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¢¼", C_PUPPLE);
	}
};

class Flame : public Object
{
protected:
	bool sweep;

public:
	Flame(Position position) : Object(position)
	{
		sweep = false;
	}

	bool CheckSweep()
	{
		return sweep;
	}

	void Sweep()
	{
		sweep = true;
	}

	void Draw()
	{
		DrawPoint(position.x, position.y, "¡Ü", C_RED);
	}
};

class Crypt_Raider : public Game
{
protected:
	int level;

	vector<Wall*> wall;
	vector<Stone*> stone;
	vector<Sand*> sand;
	Door* door;
	Portal* portal;
	Key* key;
	vector<Marble*> marble;
	vector<Rock*> rock;
	vector<Bug*> bug;
	Player* player;

	vector<Flame*> flame;

	Clock marbleClock;
	Clock rockClock;
	Clock bugClock;

	int marbleTime;
	int rockTime;
	int bugTime;

public:
	Crypt_Raider()
	{
		SetScreenSize(WIDTH, HEIGHT);

		level = 2;

		LoadMap();

		marbleTime = 250;
		rockTime = 250;
		bugTime = 400;

		marbleClock.SetTime(marbleTime);
		rockClock.SetTime(rockTime);
		bugClock.SetTime(bugTime);

		Draw();
	}

	void LoadMap()
	{
		string line;
		ifstream file("lv" + to_string(level) + ".txt");

		int readCount = 0;

		while (file >> line)
		{
			Position pos = { readCount % WIDTH, readCount / WIDTH };

			if (line == "01")
				wall.push_back(new Wall(pos));

			if (line == "02")
				stone.push_back(new Stone(pos));

			if (line == "03")
				sand.push_back(new Sand(pos));

			if (line == "04")
				door = new Door(pos);

			if (line == "06")
				key = new Key(pos);

			if (line == "07")
				marble.push_back(new Marble(pos));

			if (line == "08")
				rock.push_back(new Rock(pos));

			if (line == "10")
				bug.push_back(new Bug(pos));

			if (line == "12")
				player = new Player(pos);

			if (line == "05")
				portal = new Portal(pos, (int)marble.size());

			readCount++;
		}

		file.close();
	}

	bool CheckObjectIsExistByPosition(Position position)
	{
		if (GetObjectByPosition(wall, position) != NULL)
			return true;

		if (GetObjectByPosition(stone, position) != NULL)
			return true;

		if (GetObjectByPosition(sand, position) != NULL)
			return true;

		if (GetObjectByPosition(door, position) != NULL)
			return true;

		if (GetObjectByPosition(portal, position) != NULL)
			return true;

		if (GetObjectByPosition(key, position) != NULL)
			return true;

		if (GetObjectByPosition(marble, position) != NULL)
			return true;

		if (GetObjectByPosition(rock, position) != NULL)
			return true;

		if (GetObjectByPosition(bug, position) != NULL)
			return true;

		if (GetObjectByPosition(player, position) != NULL)
			return true;

		return false;
	}

	void Boom(Position position)
	{
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
				flame.push_back(new Flame({ position.x + x, position.y + y }));
		}

		Draw();
	}

	void PlayerEvent()
	{
		if (player != NULL)
		{
			Position playerPos = player->position;
			Position checkPortalPos = playerPos;

			checkPortalPos.y++;

			Portal* enterPortal = GetObjectByPosition(portal, checkPortalPos);

			if (enterPortal != NULL && enterPortal->CheckFull())
			{
				DeleteWhole();

				level++;

				LoadMap();
				Draw();
			}
			else
			{
				Position beyondMarblePos = playerPos;

				switch (Hit())
				{
				case LEFT:
					playerPos.x--;
					beyondMarblePos.x -= 2;
					break;

				case RIGHT:
					playerPos.x++;
					beyondMarblePos.x += 2;
					break;

				case UP:
					playerPos.y--;
					break;

				case DOWN:
					playerPos.y++;
					break;
				}

				if (playerPos != player->position)
				{
					if (GetObjectByPosition(wall, playerPos) == NULL)
					{
						if (GetObjectByPosition(portal, playerPos) == NULL)
						{
							if (GetObjectByPosition(stone, playerPos) == NULL)
							{
								Marble* pushMarble = GetObjectByPosition(marble, playerPos);
								Rock* pushRock = GetObjectByPosition(rock, playerPos);

								if (pushMarble != NULL)
								{
									if (pushMarble->position.y == player->position.y)
									{
										if (CheckObjectIsExistByPosition(beyondMarblePos) == false)
										{
											player->position = playerPos;
											pushMarble->position = beyondMarblePos;
										}
									}
								}
								else if (pushRock != NULL)
								{
									if (pushRock->position.y == player->position.y)
									{
										if (CheckObjectIsExistByPosition(beyondMarblePos) == false)
										{
											player->position = playerPos;
											pushRock->position = beyondMarblePos;
										}
									}
								}
								else
									player->position = playerPos;
							}
						}
					}

					Draw();
				}
			}
		}
	}

	void MarbleEvent()
	{
		for (int i = 0; i < marble.size(); i++)
		{
			if (marble[i] != NULL)
			{
				Position marblePos = marble[i]->position;

				if (GetObjectByPosition(portal, marblePos) != NULL)
				{
					portal->InsertMarble(marble[i]);
					Draw();
				}
				else
				{
					marblePos.y++;

					if (CheckObjectIsExistByPosition(marblePos) == false || GetObjectByPosition(portal, marblePos) != NULL)
					{
						if (marble[i]->CheckFalling() == false)
						{
							marble[i]->SetFalling(true);
							marbleClock.SetTime(marbleTime);

							Draw();
						}
						else
						{
							if (marbleClock.Alarm())
							{
								marble[i]->MoveDown();

								Draw();
							}
						}
					}
					else
						marble[i]->SetFalling(false);
				}
			}
		}
	}

	void SandEvent()
	{
		for (int i = 0; i < sand.size(); i++)
		{
			if (sand[i] != NULL)
			{
				Position sandPos = sand[i]->position;

				if (GetObjectByPosition(player, sandPos) != NULL)
					Delete(sand[i]);
			}
		}
	}

	void RockEvent()
	{
		for (int i = 0; i < rock.size(); i++)
		{
			if (rock[i] != NULL)
			{
				Position rockPos = rock[i]->position;

				if (GetObjectByPosition(flame, rockPos) != NULL)
					Delete(rock[i]);
				else
				{
					rockPos.y++;

					if (CheckObjectIsExistByPosition(rockPos) == false)
					{
						if (rock[i]->CheckFalling() == false)
						{
							rock[i]->SetFalling(true);
							rockClock.SetTime(rockTime);

							Draw();
						}
						else
						{
							if (rockClock.Alarm())
							{
								rock[i]->MoveDown();

								Draw();
							}
						}
					}
					else if (GetObjectByPosition(bug, rockPos) != NULL)
					{
						if (rock[i]->CheckFalling() == true)
							Boom(rock[i]->position);
					}
					else
						rock[i]->SetFalling(false);
				}
			}
		}
	}

	void BugEvent()
	{
		for (int i = 0; i < bug.size(); i++)
		{
			if (bug[i] != NULL)
			{
				Position bugPos = bug[i]->position;

				if (GetObjectByPosition(flame, bugPos) != NULL)
					Delete(bug[i]);
				else if (bugClock.Alarm())
				{
					int direction = bug[i]->GetDirection();

					Position forwardPos = bugPos;

					switch (direction)
					{
					case LEFT:
						forwardPos.x--;
						break;

					case RIGHT:
						forwardPos.x++;
						break;

					case UP:
						forwardPos.y--;
						break;

					case DOWN:
						forwardPos.y++;
						break;
					}

					Position diagonalPos = forwardPos;

					switch (direction)
					{
					case LEFT:
						diagonalPos.y++;
						break;

					case RIGHT:
						diagonalPos.y--;
						break;

					case UP:
						diagonalPos.x--;
						break;

					case DOWN:
						diagonalPos.x++;
						break;
					}

					if (CheckObjectIsExistByPosition(forwardPos) == false || GetObjectByPosition(player, forwardPos) != NULL)
					{
						bug[i]->Move();

						Draw();

						if (CheckObjectIsExistByPosition(diagonalPos) == false || GetObjectByPosition(player, diagonalPos) != NULL)
							bug[i]->RotateDirectionRevert();
					}
					else
						bug[i]->RotateDirection();
				}
			}
		}
	}

	void StoneEvent()
	{
		for (int i = 0; i < stone.size(); i++)
		{
			if (stone[i] != NULL)
			{
				Position stonePos = stone[i]->position;

				if (GetObjectByPosition(flame, stonePos) != NULL)
					Delete(stone[i]);
			}
		}
	}

	void FlameEvent()
	{
		for (int i = 0; i < flame.size(); i++)
		{
			if (flame[i] != NULL)
			{
				if (flame[i]->CheckSweep() == true)
				{
					Delete(flame[i]);

					Draw();
				}
				else
					flame[i]->Sweep();
			}
		}
	}

	bool Update()
	{
		if (Hit() == ESC)
		{
			DeleteWhole();
			LoadMap();
			Draw();
		}

		PlayerEvent();
		MarbleEvent();
		SandEvent();
		RockEvent();
		BugEvent();
		StoneEvent();

		FlameEvent();

		Sleep(33);

		return true;
	}

	void Draw()
	{
		system("cls");

		DrawObject(wall);
		DrawObject(stone);
		DrawObject(sand);
		DrawObject(door);
		DrawObject(portal);
		DrawObject(key);
		DrawObject(marble);
		DrawObject(rock);
		DrawObject(bug);
		DrawObject(player);
		DrawObject(flame);
	}

	void DeleteWhole()
	{
		Delete(wall);
		Delete(stone);
		Delete(sand);
		Delete(door);
		Delete(portal);
		Delete(key);
		Delete(marble);
		Delete(rock);
		Delete(bug);
		Delete(player);
		Delete(flame);
	}

	~Crypt_Raider()
	{
		DeleteWhole();
	}
};

int main()
{
	Crypt_Raider* game = new Crypt_Raider;

	game->Play();

	Delete(game);

	return 0;
}
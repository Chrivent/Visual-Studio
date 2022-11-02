#include "C:\Users\USER\Desktop\Visual-Studio\Cpp Mecro\mecro.h"

using namespace cMecro;

class Body : public Object
{
private:
	bool head;

public:
	Body()
	{
		head = false;
	}

	void ActivateHead()
	{
		head = true;
	}

	void Draw()
	{
		DrawPoint(position.x, position.y, head ? "¢Ã" : "¡á", head ? C_HIGH_GREEN : C_SKY_BLUE);
	}
};

struct Node : public Body
{
	Node* next;

	Node()
	{
		next = nullptr;
	}

	Node(Position position)
	{
		this->position = position;

		next = nullptr;
	}
};

class LinkedList
{
private:
	Node* head;
	int length;

public:
	LinkedList()
	{
		head = new Node;

		length = 0;
	}

	void Insert(int index, Position position)
	{
		if (index < 0 || index > length)
			return;
		else
		{
			Node* prevNode = head;

			for (int i = 0; i < index; i++)
				prevNode = prevNode->next;

			Node* nextNode = prevNode->next;
			Node* indexNode = new Node(position);

			prevNode->next = indexNode;
			indexNode->next = nextNode;

			length++;
		}
	}

	Node* GetNode(int index)
	{
		if (index < 0 || index >= length)
			return nullptr;
		else
		{
			Node* prevNode = head;

			for (int i = 0; i < index; i++)
				prevNode = prevNode->next;

			Node* indexNode = prevNode->next;

			return indexNode;
		}
	}

	void Remove(int index)
	{
		if (index < 0 || index >= length)
			return;
		else
		{
			Node* prevNode = head;

			for (int i = 0; i < index; i++)
				prevNode = prevNode->next;

			Node* indexNode = prevNode->next;
			Node* nextNode = indexNode->next;

			delete indexNode;

			indexNode = nullptr;

			prevNode->next = nextNode;

			length--;
		}
	}

	void RemoveAll()
	{
		int tmp = length;

		for (int i = 0; i < tmp; i++)
			Remove(0);
	}

	int GetLength()
	{
		return length;
	}

	~LinkedList()
	{
		RemoveAll();

		delete head;

		head = nullptr;
	}
};

class Food : public Object
{
public:
	void Draw()
	{
		DrawPoint(position.x, position.y, "¡Ü", C_RED);
	}
};

enum SCENE
{
	SCENE_MAINMENU,
	SCENE_PLAY,
	SCENE_LEVEL,
	SCENE_EXIT
};

enum MAINMENU
{
	MAINMENU_PLAY,
	MAINMENU_LEVEL,
	MAINMENU_EXIT
};

enum LEVELMENU
{
	LEVELMENU_EASY,
	LEVELMENU_NORMAL,
	LEVELMENU_HARD
};

enum PLAYSIZE
{
	PLAYSIZE_EASY = 20,
	PLAYSIZE_NORMAL = 30,
	PLAYSIZE_HARD = 40
};

enum MOVECLOCK
{
	MOVECLOCK_EASY = 300,
	MOVECLOCK_NORMAL = 200,
	MOVECLOCK_HARD = 100
};

class SnakeGame : public Game
{
private:
	LinkedList bodys;
	Clock moveClock;
	Food food;
	Position lastPos;

	int mainSize;
	int mainSelect;
	int levelSelect;
	int playSize;
	bool init;
	int direction;

	void DrawMainMenu()
	{
		DrawBox(0, 0, mainSize, mainSize, C_PUPPLE);
		DrawTextMiddle(mainSize / 2, mainSize / 4, "[ Snake Game ]", C_PLUM);
		DrawTextMiddle(mainSize / 2, mainSize / 2, "Start", mainSelect == MAINMENU_PLAY ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 5 * 3, "Level", mainSelect == MAINMENU_LEVEL ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 10 * 7, "Exit", mainSelect == MAINMENU_EXIT ? C_GREEN : C_GRAY);
	}

	void DrawLevelMenu()
	{
		DrawBox(0, 0, mainSize, mainSize, C_PUPPLE);
		DrawTextMiddle(mainSize / 2, mainSize / 4, "Easy", levelSelect == LEVELMENU_EASY ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 2, "Normal", levelSelect == LEVELMENU_NORMAL ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 4 * 3, "Hard", levelSelect == LEVELMENU_HARD ? C_GREEN : C_GRAY);
	}

	void SetLevel()
	{
		switch (levelSelect)
		{
		case LEVELMENU_EASY:
			moveClock.SetTime(MOVECLOCK_EASY);

			playSize = PLAYSIZE_EASY;
			break;

		case LEVELMENU_NORMAL:
			moveClock.SetTime(MOVECLOCK_NORMAL);

			playSize = PLAYSIZE_NORMAL;
			break;

		case LEVELMENU_HARD:
			moveClock.SetTime(MOVECLOCK_HARD);

			playSize = PLAYSIZE_HARD;
			break;
		}
	}

	void SetFoodPositionRand()
	{
		bool check = true;

		while (check)
		{
			check = false;

			food.position = { RandNum(1, playSize - 1), RandNum(1, playSize - 1) };

			for (int i = 0; i < bodys.GetLength(); i++)
			{
				if (bodys.GetNode(i)->position == food.position)
					check = true;
			}
		}
	}

	void Init()
	{
		SetScreenSize(playSize, playSize);

		int center = playSize / 2;

		bodys.Insert(0, { center, center });
		bodys.GetNode(0)->ActivateHead();

		direction = NULL;

		SetFoodPositionRand();
		Draw();

		init = true;
	}

	void Move(int index, Position position)
	{
		Position pos = bodys.GetNode(index)->position;

		bodys.GetNode(index)->position = position;

		index++;

		if (index < bodys.GetLength())
			Move(index, pos);
		else
			lastPos = pos;

		return;
	}

	bool CheckGameOver(Position headPos)
	{
		for (int i = 1; i < bodys.GetLength(); i++)
		{
			if (bodys.GetNode(i)->position == headPos)
				return true;
		}

		if (headPos.x == 0 || headPos.x == playSize - 1)
			return true;

		if (headPos.y == 0 || headPos.y == playSize - 1)
			return true;

		return false;
	}

	void GameOver()
	{
		bodys.RemoveAll();

		scene = SCENE_MAINMENU;

		SetScreenSize(mainSize, mainSize);
		Draw();

		init = false;
	}

	void MainMenuScene()
	{
		switch (Hit())
		{
		case UP:
			if (mainSelect > MAINMENU_PLAY)
			{
				mainSelect--;

				Draw();
			}
			break;

		case DOWN:
			if (mainSelect < MAINMENU_EXIT)
			{
				mainSelect++;

				Draw();
			}
			break;

		case ENTER:
			scene = mainSelect + 1;

			if (scene == SCENE_LEVEL)
				Draw();
			break;
		}
	}

	void PlayScene()
	{
		if (init == false)
			Init();
		else
		{
			if (moveClock.Alarm())
			{
				Position headPos = bodys.GetNode(0)->position;

				switch (direction)
				{
				case LEFT:
					headPos.x--;
					break;

				case RIGHT:
					headPos.x++;
					break;

				case UP:
					headPos.y--;
					break;

				case DOWN:
					headPos.y++;
				}

				Move(0, headPos);

				if (headPos == food.position)
				{
					bodys.Insert(bodys.GetLength(), lastPos);

					SetFoodPositionRand();
				}
				else if (CheckGameOver(headPos))
				{
					GameOver();

					return;
				}

				Draw();
			}
		}

		int hit = Hit();

		if (hit == LEFT || hit == RIGHT || hit == UP || hit == DOWN)
			direction = hit;
		else if (hit == ESC)
		{
			GameOver();

			return;
		}
	}

	void LevelScene()
	{
		int tmp = levelSelect;

		switch (Hit())
		{
		case UP:
			if (levelSelect > LEVELMENU_EASY)
			{
				levelSelect--;

				Draw();
			}
			break;

		case DOWN:
			if (levelSelect < LEVELMENU_HARD)
			{
				levelSelect++;

				Draw();
			}
			break;

		case ENTER:
			SetLevel();

			scene = SCENE_MAINMENU;

			Draw();
			break;

		case ESC:
			switch (playSize)
			{
			case PLAYSIZE_EASY:
				levelSelect = LEVELMENU_EASY;
				break;

			case PLAYSIZE_NORMAL:
				levelSelect = LEVELMENU_NORMAL;
				break;

			case PLAYSIZE_HARD:
				levelSelect = LEVELMENU_HARD;
				break;
			}

			scene = SCENE_MAINMENU;

			Draw();
			break;
		}
	}

	void Draw()
	{
		system("cls");

		switch (scene)
		{
		case SCENE_MAINMENU:
			DrawMainMenu();
			break;

		case SCENE_PLAY:
			for (int i = 0; i < bodys.GetLength(); i++)
				bodys.GetNode(i)->Draw();

			DrawEmptyRectangle(0, 0, playSize, playSize, "¢Ì");

			food.Draw();
			break;

		case SCENE_LEVEL:
			DrawLevelMenu();
			break;
		}
	}

	void Start()
	{
		mainSelect = MAINMENU_PLAY;
		levelSelect = LEVELMENU_NORMAL;

		SetLevel();
		SetScreenSize(mainSize, mainSize);
		Draw();
	}

	bool Update()
	{
		switch (scene)
		{
		case SCENE_MAINMENU:
			MainMenuScene();
			break;

		case SCENE_PLAY:
			PlayScene();
			break;

		case SCENE_LEVEL:
			LevelScene();
			break;

		case SCENE_EXIT:
			return false;
		}

		return true;
	}

public:
	SnakeGame()
	{
		mainSize = 20;
		mainSelect = MAINMENU_PLAY;
		levelSelect = LEVELMENU_NORMAL;
		playSize = PLAYSIZE_NORMAL;
		init = false;
		direction = NULL;
	}
};

int main()
{
	SnakeGame snakeGame;

	snakeGame.Play();

	return 0;
}
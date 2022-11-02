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
		DrawPoint(position.x, position.y, "¢Ã", head ? C_HIGH_GREEN : C_SKY_BLUE);
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
		for (int i = 0; i < length; i++)
			Remove(i);
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
	int playSize;
	bool start;
	int direction;

	void DrawMainMenu()
	{
		DrawBox(0, 0, mainSize, mainSize, C_PUPPLE);
		DrawTextMiddle(mainSize / 2, mainSize / 4, "[ Snake Game ]", C_PLUM);
		DrawTextMiddle(mainSize / 2, mainSize / 2, "Start", mainSelect == MAINMENU_PLAY ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 5 * 3, "Level", mainSelect == MAINMENU_LEVEL ? C_GREEN : C_GRAY);
		DrawTextMiddle(mainSize / 2, mainSize / 10 * 7, "Exit", mainSelect == MAINMENU_EXIT ? C_GREEN : C_GRAY);
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

	void Start()
	{
		SetScreenSize(playSize, playSize);

		Node* head = bodys.GetNode(0);
		int center = playSize / 2;

		head->position = { center, center };
		head->ActivateHead();

		SetFoodPositionRand();

		Draw();

		start = true;
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

public:
	SnakeGame()
	{
		bodys.Insert(0, { 0, 0 });
		moveClock.SetTime(MOVECLOCK_NORMAL);

		mainSize = 20;
		mainSelect = MAINMENU_PLAY;
		playSize = PLAYSIZE_NORMAL;
		start = false;
		direction = NULL;

		SetScreenSize(mainSize, mainSize);
		Draw();
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
			DrawEmptyRectangle(0, 0, playSize, playSize, "¢Ì");

			for (int i = 0; i < bodys.GetLength(); i++)
				bodys.GetNode(i)->Draw();

			food.Draw();
			break;
		}
	}

	bool Update()
	{
		int hit = Hit();
		Position headPos;

		switch (scene)
		{
		case SCENE_MAINMENU:
			switch (hit)
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
				break;
			}
			break;

		case SCENE_PLAY:
			if (start == false)
				Start();
			else
			{
				if (moveClock.Alarm())
				{
					headPos = bodys.GetNode(0)->position;

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

					Draw();
				}
			}

			if (hit != NULL)
				direction = hit;
			break;

		case SCENE_LEVEL:
			break;

		case SCENE_EXIT:
			return false;
		}

		return true;
	}
};

int main()
{
	SnakeGame snakeGame;

	snakeGame.Play();

	return 0;
}
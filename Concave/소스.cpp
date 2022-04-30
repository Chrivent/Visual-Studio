#include "C:\Users\USER\Desktop\Visual-Studio\Cpp Mecro\mecro.h"

using namespace cMecro;

class Stone : public Object
{
protected:
	int color;

public:
	Stone(int color)
	{
		this->color = color;
	}

	void Draw()
	{
		DrawPoint(position.x, position.y, "б▄", color);
	}
};

class Cursor : public Object
{
public:
	void Draw()
	{
		DrawPoint(position.x, position.y, "б█", C_BLUE);
	}
};

class Map : public Object
{
protected:
	Scale scale;

public:
	Map()
	{
		scale = { 15, 15 };
	}

	Scale GetScale()
	{
		return scale;
	}

	void Draw()
	{
		DrawGrid(position.x, position.y, scale.width, scale.height, C_PUPPLE);
	}
};

class ConcaveAI
{
protected:
	//int** weight;
	int lineCount;
	int countToWin;
	vector<Stone*>* enemyStone;
	vector<Stone*>* myStone;

public:
	ConcaveAI(vector<Stone*>* enemyStone, vector<Stone*>* myStone, int lineCount = 15, int countToWin = 5)
	{
		/*weight = new int* [lineCount];

		for (int y = 0; y < lineCount; y++)
			weight[y] = new int[lineCount];*/

		this->enemyStone = enemyStone;
		this->myStone = myStone;
		this->lineCount = lineCount;
		this->countToWin = countToWin;
	}

	bool CheckEnemyStone(Position position)
	{
		for (int i = 0; i < (int)enemyStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL && enemyStone->at(i)->position == position)
				return true;
		}

		return false;
	}

	/*void SetWeightToStone()
	{
		for (int i = 0; i < (int)enemyStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL)
			{
				Position stonePos = enemyStone->at(i)->position;

				weight[stonePos.y][stonePos.x] = 1;
			}
		}

		for (int i = 0; i < (int)myStone->size(); i++)
		{
			if (myStone->at(i) != NULL)
			{
				Position stonePos = myStone->at(i)->position;

				weight[stonePos.y][stonePos.x] = 1;
			}
		}
	}*/

	/*void SetWeightToPreventDanger(vector<Stone*>* enemyStone, vector<Stone*>* myStone, int dangerLevel, int checkCount)
	{
		int maxWeight = -(int)pow(lineCount, 2) * dangerLevel;

		for (int i = 0; i < (int)enemyStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL)
			{
				Position pos = enemyStone->at(i)->position;

				bool widthLine = true;
				bool heightLine = true;
				bool diagonalLine = true;
				bool diagonalRevertLine = true;

				for (int i = 1; i < checkCount; i++)
				{
					if (!CheckEnemyStone({ pos.x + i, pos.y }))
						widthLine = false;

					if (!CheckEnemyStone({ pos.x, pos.y + i }))
						heightLine = false;

					if (!CheckEnemyStone({ pos.x + i, pos.y + i }))
						diagonalLine = false;

					if (!CheckEnemyStone({ pos.x - i, pos.y + i }))
						diagonalRevertLine = false;
				}

				if (widthLine == true)
				{
					if (!(pos.x - 1 < 0))
						weight[pos.y][pos.x - 1] = maxWeight;

					if (!(pos.x + checkCount >= lineCount))
						weight[pos.y][pos.x + checkCount] = maxWeight;
				}

				if (heightLine == true)
				{
					if (!(pos.y - 1 < 0))
						weight[pos.y - 1][pos.x] = maxWeight;

					if (!(pos.y + checkCount >= lineCount))
						weight[pos.y + checkCount][pos.x] = maxWeight;
				}

				if (diagonalLine == true)
				{
					if (!(pos.x - 1 < 0 || pos.y - 1 < 0))
						weight[pos.y - 1][pos.x - 1] += maxWeight;

					if (!(pos.x + checkCount >= lineCount || pos.y + checkCount >= lineCount))
						weight[pos.y + checkCount][pos.x + checkCount] = maxWeight;
				}

				if (diagonalRevertLine == true)
				{
					if (!(pos.x + 1 >= lineCount || pos.y - 1 < 0))
						weight[pos.y - 1][pos.x + 1] += maxWeight;

					if (!(pos.x - checkCount < 0 || pos.y + checkCount >= lineCount))
						weight[pos.y + checkCount][pos.x - checkCount] = maxWeight;
				}
			}
		}
	}*/

	/*Position GetPositionToPutStoneToWin()
	{
		Position posToWin;

		for (int y = 0; y < lineCount; y++)
		{
			for (int x = 0; x < lineCount; x++)
				weight[y][x] = 0;
		}

		for (int i = 0; i < (int)enemyStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL)
			{
				Position stonePos = enemyStone->at(i)->position;

				for (int j = -1; j <= 1; j++)
				{
					for (int k = -1; k <= 1; k++)
					{
						int ySum = stonePos.y + j;
						int xSum = stonePos.x + k;

						if (!(ySum < 0 || ySum >= lineCount || xSum < 0 || xSum >= lineCount))
						{
							if (!(j == 0 && k == 0))
								weight[stonePos.y + j][stonePos.x + k]--;
						}
					}
				}
			}
		}

		for (int i = 0; i < (int)myStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL)
			{
				Position stonePos = enemyStone->at(i)->position;

				for (int j = -1; j <= 1; j++)
				{
					for (int k = -1; k <= 1; k++)
					{
						int ySum = stonePos.y + j;
						int xSum = stonePos.x + k;

						if (!(ySum < 0 || ySum >= lineCount || xSum < 0 || xSum >= lineCount))
						{
							if (!(j == 0 && k == 0))
								weight[stonePos.y + j][stonePos.x + k]++;
						}
					}
				}
			}
		}

		SetWeightToStone();
		//SetWeightToPreventDanger(enemyStone, myStone, 1, countToWin - 2);
		//SetWeightToPreventDanger(enemyStone, myStone, 2, countToWin - 1);
		//SetWeightToStone();

		int min = 0;

		for (int y = 0; y < lineCount; y++)
		{
			for (int x = 0; x < lineCount; x++)
			{
				if (weight[y][x] < min)
					min = weight[y][x];
			}
		}

		vector<Position> pos;

		for (int y = 0; y < lineCount; y++)
		{
			for (int x = 0; x < lineCount; x++)
			{
				if (weight[y][x] == min)
					pos.push_back({ x, y });
			}
		}

		posToWin = pos[RandNum(0, pos.size())];

		return posToWin;
	}*/

	bool CheckEnemyWin()
	{
		for (int i = 0; i < (int)enemyStone->size(); i++)
		{
			if (enemyStone->at(i) != NULL)
			{
				Position pos = enemyStone->at(i)->position;

				bool widthLine = true;
				bool heightLine = true;
				bool diagonalLine = true;
				bool diagonalRevertLine = true;

				for (int i = 0; i < countToWin; i++)
				{
					if (!CheckEnemyStone({ pos.x + i, pos.y }))
						widthLine = false;

					if (!CheckEnemyStone({ pos.x, pos.y + i }))
						heightLine = false;

					if (!CheckEnemyStone({ pos.x + i, pos.y + i }))
						diagonalLine = false;

					if (!CheckEnemyStone({ pos.x - i, pos.y + i }))
						diagonalRevertLine = false;
				}

				if (widthLine || heightLine || diagonalLine || diagonalRevertLine)
					return true;
			}
		}

		return false;
	}

	bool CheckStoneExist(Position pos)
	{
		if (CheckEnemyStone(pos))
			return true;

		for (int i = 0; i < (int)myStone->size(); i++)
		{
			if (myStone->at(i) != NULL && myStone->at(i)->position == pos)
				return true;
		}

		return false;
	}

	bool CheckDanger(Position pos, int checkCount = 0)
	{
		if (checkCount == 2)
			return false;

		checkCount++;

		Stone* stone1 = new Stone(NULL);
		stone1->position = pos;
		myStone->push_back(stone1);

		for (int y1 = 0; y1 < lineCount; y1++)
		{
			for (int x1 = 0; x1 < lineCount; x1++)
			{
				if (!CheckStoneExist({ x1, y1 }))
				{
					Stone* stone2 = new Stone(NULL);
					stone2->position = { x1, y1 };
					enemyStone->push_back(stone2);

					if (CheckEnemyWin())
					{
						delete stone2;
						stone2 = NULL;
						enemyStone->pop_back();

						delete stone1;
						stone1 = NULL;
						myStone->pop_back();

						return true;
					}
					else
					{
						for (int y2 = 0; y2 < lineCount; y2++)
						{
							for (int x2 = 0; x2 < lineCount; x2++)
							{
								if (!CheckStoneExist({ x2, y2 }) && CheckDanger({ x2, y2 }, checkCount))
								{
									delete stone2;
									stone2 = NULL;
									enemyStone->pop_back();

									delete stone1;
									stone1 = NULL;
									myStone->pop_back();

									return true;
								}
							}
						}
					}

					delete stone2;
					stone2 = NULL;
					enemyStone->pop_back();
				}
			}
		}

		delete stone1;
		stone1 = NULL;
		myStone->pop_back();

		return false;
	}

	Position Put()
	{
		Position put;

		do
			put = { RandNum(0, lineCount), RandNum(0, lineCount) };
		while (CheckStoneExist(put) || CheckDanger(put));

		return put;
	}

	/*void DrawWeight()
	{
		SetWeightToStone();

		for (int y = 0; y < lineCount; y++)
		{
			for (int x = 0; x < lineCount; x++)
			{
				int var = weight[y][x];

				if (weight[y][x] > 0)
				{
					DrawPoint(x + lineCount, y, "бс", C_ORIGINAL);
				}
				else if (weight[y][x] < 0 && weight[y][x] > -10)
				{
					DrawPoint(x + lineCount, y, "бс", C_HIGH_GREEN);
				}
				else if (weight[y][x] <= -10 && weight[y][x] > -100)
				{
					DrawPoint(x + lineCount, y, "бс", C_BLUE_GREEN);
				}
				else if (weight[y][x] <= -100)
				{
					DrawPoint(x + lineCount, y, "бс", C_GREEN);
				}
				else
				{
					DrawPoint(x + lineCount, y, "  ");
				}
			}
		}
	}*/

	~ConcaveAI()
	{
		/*for (int i = 0; i < lineCount; i++)
		{
			delete[] weight[i];
			weight[i] = NULL;
		}

		delete[] weight;
		weight = NULL;*/
	}
};

class Concave
{
protected:
	Map* map;
	vector<Stone*> playerStone;
	vector<Stone*> computerStone;
	Cursor* cursor;
	string team;
	ConcaveAI* ai;

public:
	Concave()
	{
		map = new Map;

		Scale mapSca = map->GetScale();

		SetScreenSize(mapSca.width * 2, mapSca.height);

		cursor = new Cursor;
		cursor->position = { mapSca.width / 2, mapSca.height / 2 };

		team = "Player";

		ai = new ConcaveAI(&playerStone, &computerStone);

		Draw();
	}

	void PutPlayerStone(int color)
	{
		Stone* stone = new Stone(color);
		stone->position = cursor->position;
		playerStone.push_back(stone);
		team = "Computer";
	}

	void PutComputerStone(Position position, int color)
	{
		Stone* stone = new Stone(color);
		stone->position = position;
		computerStone.push_back(stone);
		team = "Player";
	}

	bool CheckCursorIsOnStone()
	{
		Position cursorPos = cursor->position;

		for (int i = 0; i < (int)playerStone.size(); i++)
		{
			if (playerStone[i] != NULL && playerStone[i]->position == cursorPos)
				return true;
		}

		for (int i = 0; i < (int)computerStone.size(); i++)
		{
			if (computerStone[i] != NULL && computerStone[i]->position == cursorPos)
				return true;
		}

		return false;
	}

	bool Update()
	{
		if (team == "Player")
		{
			int hit = Hit();

			if (hit != NULL)
			{
				switch (hit)
				{
				case LEFT:
					cursor->MoveLeft();
					break;

				case RIGHT:
					cursor->MoveRight();
					break;

				case UP:
					cursor->MoveUp();
					break;

				case DOWN:
					cursor->MoveDown();
					break;

				case SPACE:
					if (CheckCursorIsOnStone() == false)
						PutPlayerStone(C_ORIGINAL);
					break;
				}

				Draw();
			}
		}
		else
		{
			PutComputerStone(ai->Put(), C_GRAY);

			Draw();
		}

		return true;
	}

	void Draw()
	{
		map->Draw();

		for (int i = 0; i < (int)playerStone.size(); i++)
		{
			if (playerStone[i] != NULL)
				playerStone[i]->Draw();
		}

		for (int i = 0; i < (int)computerStone.size(); i++)
		{
			if (computerStone[i] != NULL)
				computerStone[i]->Draw();
		}

		cursor->Draw();
		//ai->DrawWeight();
	}

	~Concave()
	{
		delete map;
		map = NULL;

		delete cursor;
		cursor = NULL;

		delete ai;
		ai = NULL;
	}
};

int main()
{
	Concave* concave;
	concave = new Concave;

	while (concave->Update());

	delete concave;
	concave = NULL;

	return 0;
}
#include "AStar.h"
#include "PacMan.h"

AStar::AStar(int** map, int width, int height) : map(map), width(width), height(height)
{
	foundPath = false;

	weightMap = new int* [height];
	visitMap = new bool* [height];

	for (int i = 0; i < height; i++)
	{
		weightMap[i] = new int[width];
		visitMap[i] = new bool[width];
	}

	ResetWeightAndVisit();

	debug = false;
}

AStar::~AStar()
{
	if (weightMap)
	{
		for (int y = 0; y < height; y++)
			Delete(weightMap[y]);
		Delete(weightMap);
	}

	if (visitMap)
	{
		for (int y = 0; y < height; y++)
			Delete(visitMap[y]);
		Delete(visitMap);
	}

	ReleaseParent();
}

bool AStar::FindPath(Position startPos, Position endPos, vector<Path*> paths, int cellWidth, int cellHeight)
{
	foundPath = false;

	parentPoses = new Position * [height];

	for (int i = 0; i < height; i++)
		parentPoses[i] = new Position[width];

	SetWeight(startPos, 0);

	Position choicePos = startPos;
	parentPoses[startPos.y][startPos.x] = choicePos;

	for (int i = 0; i < width * height; i++)
	{
		SetVisit(choicePos, true);
		visitNodes.push_back(choicePos);
		
		if (choicePos == endPos)
		{
			foundPath = true;
			break;
		}

		if (debug)
		{
			for (int j = 0; j < paths.size(); j++)
			{
				Position pathPosition = paths[j]->transform.position;

				if (pathPosition.x == choicePos.x * cellWidth && pathPosition.y == choicePos.y * cellHeight)
					paths[j]->debugVisit = true;
			}
		}

		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if ((x == 0) != (y == 0))
				{
					Position nearPos = { choicePos.x + x, choicePos.y + y };

					if (!CheckIsPath(nearPos))
						continue;

					if (GetVisit(nearPos) == false)
					{
						int dist = 10;
						int cost = GetWeight(choicePos) + dist;

						if (GetWeight(nearPos) > cost)
						{
							SetWeight(nearPos, cost);
							parentPoses[nearPos.y][nearPos.x] = choicePos;
						}
					}
				}
			}
		}

		ExtractMin(choicePos, endPos);
	}

	visitNodes.clear();
	ResetWeightAndVisit();

	if (foundPath)
	{
		Position pos = endPos;
		pathPoses.push(pos);

		while (pos != startPos)
		{
			pos = parentPoses[pos.y][pos.x];
			pathPoses.push(pos);
			if (debug)
			{
				for (int j = 0; j < paths.size(); j++)
				{
					Position pathPosition = paths[j]->transform.position;

					if (pathPosition.x == pos.x * cellWidth && pathPosition.y == pos.y * cellHeight)
						paths[j]->debugToGo = true;
				}
			}
		}
		pathPoses.pop();

		ReleaseParent();
		return true;
	}

	ReleaseParent();
	return false;
}

void AStar::ClearPath(vector<Path*> paths)
{
	visitNodes.clear();
	ResetWeightAndVisit();
	ReleaseParent();

	while (!pathPoses.empty())
		pathPoses.pop();

	if (debug)
	{
		for (int j = 0; j < paths.size(); j++)
		{
			paths[j]->debugVisit = false;
			paths[j]->debugToGo = false;
		}
	}
}

void AStar::ExtractMin(Position& choicePos, Position endPos)
{
	int min = INT_MAX;

	for (int i = 0; i < visitNodes.size(); i++)
	{
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if ((x == 0) != (y == 0))
				{
					Position curPos = { visitNodes[i].x + x, visitNodes[i].y + y};

					if (!CheckIsPath(curPos))
						continue;

					int hx = abs(endPos.x - curPos.x) * 10;
					int hy = abs(endPos.y - curPos.y) * 10;
					int distance = hx + hy;

					if (GetWeight(curPos) + distance < min && GetVisit(curPos) == false)
					{
						min = GetWeight(curPos) + distance;
						choicePos = curPos;
					}
				}
			}
		}
	}
}

void AStar::ReleaseParent()
{
	if (parentPoses)
	{
		for (int y = 0; y < height; y++)
			Delete(parentPoses[y]);
		Delete(parentPoses);
	}
}

void AStar::ResetWeightAndVisit()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			weightMap[y][x] = 1000;
			visitMap[y][x] = false;
		}
	}
}

bool AStar::CheckIsPath(Position position)
{
	if (position.x >= 0 &&
		position.x < width &&
		position.y >= 0 &&
		position.y < height &&
		map[position.y][position.x] != WALL)
		return true;

	return false;
}

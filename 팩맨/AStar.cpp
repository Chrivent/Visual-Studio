#include "AStar.h"
#include "PacMan.h"

AStar::AStar(int** maps) : maps(maps)
{
	foundPath = false;

	weightMap = new int* [HEIGHT];
	visitMap = new bool* [HEIGHT];

	for (int i = 0; i < HEIGHT; i++)
	{
		weightMap[i] = new int[WIDTH];
		visitMap[i] = new bool[WIDTH];
	}

	ResetWeightAndVisit();

	debug = false;
}

AStar::~AStar()
{
	if (weightMap)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(weightMap[y]);
		Delete(weightMap);
	}

	if (visitMap)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(visitMap[y]);
		Delete(visitMap);
	}

	ReleaseParent();
}

bool AStar::FindPath(Position startGridPosition, Position endGridPosition, vector<Path*> paths, PacMan* pacMan)
{
	Scale cellScale = pacMan->GetCellScale();

	foundPath = false;

	parentGridPostions = new Position * [HEIGHT];

	for (int i = 0; i < HEIGHT; i++)
		parentGridPostions[i] = new Position[WIDTH];

	SetWeight(startGridPosition, 0);

	Position choicePosition = startGridPosition;
	parentGridPostions[startGridPosition.y][startGridPosition.x] = choicePosition;

	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		SetVisit(choicePosition, true);
		visitNodes.push_back(choicePosition);
		
		if (choicePosition == endGridPosition)
		{
			foundPath = true;
			break;
		}

		if (debug)
		{
			for (int j = 0; j < paths.size(); j++)
			{
				Position pathPosition = paths[j]->transform.position;

				if (pathPosition.x == choicePosition.x * cellScale.width && pathPosition.y == choicePosition.y * cellScale.height)
					paths[j]->SetDebugVisit(true);
			}
		}

		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if ((x == 0) != (y == 0))
				{
					Position nearPosition = { choicePosition.x + x, choicePosition.y + y };

					if (!pacMan->GridPositionIsPath(nearPosition))
						continue;

					if (GetVisit(nearPosition) == false)
					{
						int distance = 10;
						int cost = GetWeight(choicePosition) + distance;

						if (GetWeight(nearPosition) > cost)
						{
							SetWeight(nearPosition, cost);
							parentGridPostions[nearPosition.y][nearPosition.x] = choicePosition;
						}
					}
				}
			}
		}

		ExtractMin(choicePosition, endGridPosition, pacMan);
	}

	visitNodes.clear();
	ResetWeightAndVisit();

	if (foundPath)
	{
		Position tmpPosition = endGridPosition;
		pathGridPositions.push(tmpPosition);

		while (tmpPosition != startGridPosition)
		{
			tmpPosition = parentGridPostions[tmpPosition.y][tmpPosition.x];
			pathGridPositions.push(tmpPosition);

			if (debug)
			{
				for (int i = 0; i < paths.size(); i++)
				{
					Position pathPosition = paths[i]->transform.position;

					if (pathPosition.x == tmpPosition.x * cellScale.width && pathPosition.y == tmpPosition.y * cellScale.height)
						paths[i]->SetDebugToGo(true);
				}
			}
		}
		pathGridPositions.pop();

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

	while (!pathGridPositions.empty())
		pathGridPositions.pop();

	if (debug)
		ResetPathDebug(paths);
}

void AStar::SetDebug(bool debug, vector<Path*> paths)
{
	this->debug = debug;

	ResetPathDebug(paths);
}

void AStar::ExtractMin(Position& choiceGridPosition, Position endGridPosition, PacMan* pacMan)
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
					Position currentPosition = { visitNodes[i].x + x, visitNodes[i].y + y};

					if (!pacMan->GridPositionIsPath(currentPosition))
						continue;

					int distanceX = abs(endGridPosition.x - currentPosition.x) * 10;
					int distanceY = abs(endGridPosition.y - currentPosition.y) * 10;
					int distance = distanceX + distanceY;

					if (GetWeight(currentPosition) + distance < min && GetVisit(currentPosition) == false)
					{
						min = GetWeight(currentPosition) + distance;
						choiceGridPosition = currentPosition;
					}
				}
			}
		}
	}
}

void AStar::ReleaseParent()
{
	if (parentGridPostions)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(parentGridPostions[y]);
		Delete(parentGridPostions);
	}
}

void AStar::ResetWeightAndVisit()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			weightMap[y][x] = 1000;
			visitMap[y][x] = false;
		}
	}
}

void AStar::ResetPathDebug(vector<Path*> paths)
{
	for (int i = 0; i < paths.size(); i++)
	{
		paths[i]->SetDebugVisit(false);
		paths[i]->SetDebugToGo(false);
	}
}

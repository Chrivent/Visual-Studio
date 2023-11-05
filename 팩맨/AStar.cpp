#include "AStar.h"
#include "Enemy.h"
#include "Pacman.h"

AStar::AStar()
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

bool AStar::FindPath(Position startGridPosition, Position endGridPosition, Enemy* enemy, Pacman* pacman)
{
	const vector<Path*> paths = pacman->GetPaths()[enemy->GetIndex()];

	foundPath = false;

	parentGridPositions = new Position * [HEIGHT];

	for (int i = 0; i < HEIGHT; i++)
		parentGridPositions[i] = new Position[WIDTH];

	SetWeight(startGridPosition, 0);

	Position choiceGridPosition = startGridPosition;
	parentGridPositions[startGridPosition.y][startGridPosition.x] = choiceGridPosition;

	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		SetVisit(choiceGridPosition, true);
		visitNodes.push_back(choiceGridPosition);
		
		if (choiceGridPosition == endGridPosition)
		{
			foundPath = true;
			break;
		}

		if (debug)
		{
			for (Path* path : paths)
			{
				Position pathPosition = path->transform.position;

				if (pathPosition == pacman->ConvertGridPositionToPosition(choiceGridPosition))
					path->SetDebugVisit(true);
			}
		}

		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if ((x == 0) != (y == 0))
				{
					const Position nearPosition = { choiceGridPosition.x + x, choiceGridPosition.y + y };

					if (!enemy->GridPositionIsPath(nearPosition, pacman))
						continue;

					if (GetVisit(nearPosition) == false)
					{
						constexpr int distance = 10;
						const int cost = GetWeight(choiceGridPosition) + distance;

						if (GetWeight(nearPosition) > cost)
						{
							SetWeight(nearPosition, cost);
							parentGridPositions[nearPosition.y][nearPosition.x] = choiceGridPosition;
						}
					}
				}
			}
		}

		ExtractMin(choiceGridPosition, endGridPosition, enemy, pacman);
	}

	visitNodes.clear();
	ResetWeightAndVisit();

	if (foundPath)
	{
		Position tmpPosition = endGridPosition;
		pathGridPositions.push(tmpPosition);

		while (tmpPosition != startGridPosition)
		{
			tmpPosition = parentGridPositions[tmpPosition.y][tmpPosition.x];
			pathGridPositions.push(tmpPosition);

			if (debug)
			{
				for (Path* path : paths)
				{
					Position pathPosition = path->transform.position;

					if (pathPosition == pacman->ConvertGridPositionToPosition(tmpPosition))
						path->SetDebugToGo(true);
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

void AStar::ClearPath(const vector<Path*>& paths)
{
	visitNodes.clear();
	ResetWeightAndVisit();
	ReleaseParent();

	while (!pathGridPositions.empty())
		pathGridPositions.pop();

	if (debug)
		ResetPathDebug(paths);
}

void AStar::SetDebug(const bool debug, const vector<Path*>& paths)
{
	this->debug = debug;

	ResetPathDebug(paths);
}

void AStar::ExtractMin(Position& choiceGridPosition, Position endGridPosition, Enemy* enemy, const Pacman* pacman) const
{
	int min = INT_MAX;

	for (const Position& visitNode : visitNodes)
	{
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if ((x == 0) != (y == 0))
				{
					const Position currentPosition = {visitNode.x + x, visitNode.y + y};

					if (!enemy->GridPositionIsPath(currentPosition, pacman))
						continue;

					const int distanceX = abs(endGridPosition.x - currentPosition.x) * 10;
					const int distanceY = abs(endGridPosition.y - currentPosition.y) * 10;
					const int distance = distanceX + distanceY;

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
	if (parentGridPositions)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(parentGridPositions[y]);
		Delete(parentGridPositions);
	}
}

void AStar::ResetWeightAndVisit() const
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

void AStar::ResetPathDebug(const vector<Path*>& paths)
{
	for (Path* path : paths)
	{
		path->SetDebugVisit(false);
		path->SetDebugToGo(false);
	}
}

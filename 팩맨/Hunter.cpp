#include "Hunter.h"
#include "Enemy.h"
#include "PacMan.h"

Hunter& Hunter::Instance()
{
	static Hunter instance;

	return instance;
}
void Hunter::Update(Enemy* enemy, PacMan* pacMan)
{
	vector<Path*> paths = pacMan->GetPaths()[enemy->GetIndex()];
	Scale cellScale = pacMan->GetCellScale();
	int enemySpeed = pacMan->GetEnemySpeed();
	AStar* astar = enemy->GetAStar();

	int errorX = enemy->transform.position.x % cellScale.width;
	int errorY = enemy->transform.position.y % cellScale.height;

	if (errorX < enemySpeed && errorY < enemySpeed)
	{
		enemy->SetGridPosition(pacMan->ConvertPositionToGridPosition(enemy->transform.position));
		enemy->transform.position = pacMan->ConvertGridPositionToPosition(enemy->GetGridPosition());
		
		astar->ClearPath(paths);
	}
	else
	{
		int distanceX = enemy->GetTargetPosition().x - enemy->transform.position.x;
		int distanceY = enemy->GetTargetPosition().y - enemy->transform.position.y;

		if (abs(distanceX) > abs(distanceY))
			enemy->SetDirection(distanceX > 0 ? Right : Left);
		else
			enemy->SetDirection(distanceY > 0 ? Down : Up);
	}

	enemy->transform.MoveTo(enemy->GetTargetPosition(), enemySpeed);

	if (astar->GetPathGridPositions().empty())
	{
		if (enemy->DetectedPlayer(pacMan))
		{
			enemy->SetEndGridPosition(pacMan->GetPlayer()->GetGridPosition());
			enemy->SetRandFlag(true);
		}
		else
		{
			if (enemy->GetGridPosition() == enemy->GetEndGridPosition())
				enemy->SetRandFlag(true);

			if (enemy->GetRandFlag())
			{
				Position endGridPosition;
				do
				{
					endGridPosition.x = RandNum(0, WIDTH);
					endGridPosition.y = RandNum(0, HEIGHT);
				} while (!pacMan->GridPositionIsPath(endGridPosition));
				enemy->SetEndGridPosition(endGridPosition);
				enemy->SetRandFlag(false);
			}
		}

		astar->FindPath(enemy->GetGridPosition(), enemy->GetEndGridPosition(), paths, pacMan);
	}

	if (!astar->GetPathGridPositions().empty())
	{
		Position pathGridPosition = astar->GetPathGridPositions().top();
		Position pathPosition;
		pathPosition.x = pathGridPosition.x * cellScale.width + enemySpeed - 1;
		pathPosition.y = pathGridPosition.y * cellScale.height + enemySpeed - 1;
		enemy->SetTargetPosition(pathPosition);

		if (pathGridPosition == enemy->GetTargetPosition())
			astar->GetPathGridPositions().pop();
	}
}

#include "PacMan.h"

PacMan::PacMan(Scale clientScale)
{
	maps = new int* [HEIGHT];
	for (int y = 0; y < HEIGHT; y++)
	{
		maps[y] = new int[WIDTH];

		for (int x = 0; x < WIDTH; x++)
			maps[y][x] = mapData[y][x];
	}

	cellScale.width = clientScale.width / WIDTH;
	cellScale.height = clientScale.height / HEIGHT;

	debug = true;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			Position position = ConvertGridPositionToPosition({ x, y });

			if (maps[y][x] == WALL)
			{
				Wall* wall = new Wall;
				wall->transform.position = position;
				wall->transform.scale = cellScale;
				walls.push_back(wall);
			}

			if (maps[y][x] == COIN)
			{
				Coin* coin = new Coin;
				coin->transform.position = position;
				coin->transform.scale = cellScale;
				coins.push_back(coin);
			}

			if (maps[y][x] == DOOR)
			{
				Position doorPosition = position;
				doorPositions.push_back(doorPosition);
			}

			if (maps[y][x] == PLAYER)
			{
				player = new Player;
				player->transform.position = position;
				player->transform.scale = cellScale;
			}

			if (maps[y][x] == ENEMY)
			{
				Enemy* enemy = new Enemy();
				enemy->transform.position = position;
				enemy->transform.scale = cellScale;
				enemys.push_back(enemy);
			}
		}
	}

	for (int i = 0; i < enemys.size(); i++)
	{
		vector<Path*> tmpPaths;
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				Position position = ConvertGridPositionToPosition({ x, y });

				if (maps[y][x] != WALL)
				{
					Path* path = new Path;
					path->transform.position = position;
					path->transform.scale = cellScale;
					tmpPaths.push_back(path);
				}
			}
		}
		paths.push_back(tmpPaths);
	}

	playerDirection = player->GetDirection();
	player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position));
	player->SetTargetGridPosition(player->GetGridPosition());

	bool lookUp = true;
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->SetDirection(lookUp ? Up : Down);
		enemys[i]->SetIndex(i);
		Position gridPosition = ConvertPositionToGridPosition(enemys[i]->transform.position);
		enemys[i]->SetGridPosition(gridPosition);
		enemys[i]->SetTargetPosition(enemys[i]->transform.position);
		enemys[i]->SetEndGridPosition(gridPosition);

		enemys[i]->CreateAStar(maps);
		enemys[i]->GetAStar()->SetDebug(debug, paths[i]);
		enemys[i]->SetStayPositions(enemys[i]->transform.position, cellScale);

		for (int j = 0; j < paths[i].size(); j++)
			paths[i][j]->SetIndex(i);

		lookUp = !lookUp;
	}
}

PacMan::~PacMan()
{
	Delete(player);
	Delete(walls);
	Delete(coins);
	Delete(enemys);
	for (int i = 0; i < enemys.size(); i++)
		Delete(paths[i]);
	if (maps)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(maps[y]);
		Delete(maps);
	}
}

void PacMan::PlayerMoveUpdate()
{
	int errorX = player->transform.position.x % cellScale.width;
	int errorY = player->transform.position.y % cellScale.height;

	if (errorX < playerSpeed && errorY < playerSpeed)
	{
		player->SetDirection(playerDirection);

		player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position));
		player->transform.position = ConvertGridPositionToPosition(player->GetGridPosition());

		CheckCoin();
	}

	Position playerGridPosition = player->GetGridPosition();
	switch (player->GetDirection())
	{
	case Left:
		if (player->transform.position.x <= 0)
		{
			player->transform.position.x = cellScale.width * WIDTH - 1;
			playerGridPosition = ConvertPositionToGridPosition(player->transform.position);
			player->SetGridPosition(playerGridPosition);
		}

		if (CheckPlayerPath(maps[playerGridPosition.y][playerGridPosition.x - 1]))
		{
			player->transform.MoveLeft(playerSpeed);
			player->SetMoving(true);
			playerGridPosition.x--;
			player->SetTargetGridPosition(playerGridPosition);
		}
		else
			player->SetMoving(false);
		break;

	case Right:
		if (player->transform.position.x >= cellScale.width * (WIDTH - 1))
		{
			player->transform.position.x = 0;
			player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position));
		}

		if (CheckPlayerPath(maps[playerGridPosition.y][playerGridPosition.x + 1]))
		{
			player->transform.MoveRight(playerSpeed);
			player->SetMoving(true);
			playerGridPosition.x++;
			player->SetTargetGridPosition(playerGridPosition);
		}
		else
			player->SetMoving(false);
		break;

	case Up:
		if (player->transform.position.y <= 0)
		{
			player->transform.position.y = cellScale.height * HEIGHT - 1;
			player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position));
		}

		if (CheckPlayerPath(maps[playerGridPosition.y - 1][playerGridPosition.x]))
		{
			player->transform.MoveUp(playerSpeed);
			player->SetMoving(true);
			playerGridPosition.y--;
			player->SetTargetGridPosition(playerGridPosition);
		}
		else
			player->SetMoving(false);
		break;

	case Down:
		if (player->transform.position.y >= cellScale.height * (HEIGHT - 1))
		{
			player->transform.position.y = 0;
			player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position));
		}

		if (CheckPlayerPath(maps[playerGridPosition.y + 1][playerGridPosition.x]))
		{
			player->transform.MoveDown(playerSpeed);
			player->SetMoving(true);
			playerGridPosition.y++;
			player->SetTargetGridPosition(playerGridPosition);
		}
		else
			player->SetMoving(false);
		break;
	}
}

void PacMan::PlayerGaspUpdate()
{
	player->Gasp();
}

void PacMan::EnemyMoveUpdate()
{
	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Update(this);
}

void PacMan::EnemyStepUpdate()
{
	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Step();
}

void PacMan::SetPlayerDirection(Direction direction)
{
	bool canSet = false;

	switch (direction)
	{
	case Left:
		if (CheckPlayerPath(maps[player->GetTargetGridPosition().y][player->GetTargetGridPosition().x - 1]))
			canSet = true;
		break;

	case Right:
		if (CheckPlayerPath(maps[player->GetTargetGridPosition().y][player->GetTargetGridPosition().x + 1]))
			canSet = true;
		break;

	case Up:
		if (CheckPlayerPath(maps[player->GetTargetGridPosition().y - 1][player->GetTargetGridPosition().x]))
			canSet = true;
		break;

	case Down:
		if (CheckPlayerPath(maps[player->GetTargetGridPosition().y + 1][player->GetTargetGridPosition().x]))
			canSet = true;
		break;
	}

	if (canSet)
		playerDirection = direction;
}

void PacMan::OpenDoor()
{
	if (doorOpenCount < enemys.size())
		doorOpenCount++;
}

bool PacMan::GridPositionIsPath(Position position)
{
	if (position.x >= 0 &&
		position.x < WIDTH &&
		position.y >= 0 &&
		position.y < HEIGHT &&
		maps[position.y][position.x] != WALL &&
		maps[position.y][position.x] != TRANSPARENT_WALL)
		return true;

	return false;
}

Position PacMan::ConvertPositionToGridPosition(Position position)
{
	Position gridPosition;

	gridPosition.x = position.x / cellScale.width;
	gridPosition.y = position.y / cellScale.height;

	return gridPosition;
}

Position PacMan::ConvertGridPositionToPosition(Position gridPosition)
{
	Position position;

	position.x = gridPosition.x * cellScale.width;
	position.y = gridPosition.y * cellScale.height;

	return position;
}

void PacMan::Draw(HDC hdc, HWND hWnd)
{
	wMecro::DrawRectangle(hdc, wMecro::GetClientTransform(hWnd), W_BLACK);
	wMecro::DrawObject(hdc, walls);
	for (int i = (int)enemys.size() - 1; i >= 0; i--)
	{
		wMecro::DrawObject(hdc, paths[i]);

		AStar* astar = enemys[i]->GetAStar();
		if (astar->GetDebug() != debug)
			astar->SetDebug(debug, paths[i]);
	}
	for (int i = 0; i < doorPositions.size(); i++)
	{
		Position doorPosition = doorPositions[i];
		doorPosition.x += cellScale.width / 4;
		doorPosition.y += cellScale.height / 4;

		Scale doorScale = cellScale;
		doorScale.width /= 2;
		doorScale.height /= 2;

		wMecro::Transform doorTransform;
		doorTransform.position = doorPosition;
		doorTransform.scale = doorScale;

		wMecro::DrawRectangle(hdc, doorTransform, RGB(255, 128, 0));
	}
	for (int i = 0; i < enemys.size(); i++)
	{
		if (debug && enemys[i]->DetectedPlayer(this))
		{
			Position enemyPosition = enemys[i]->transform.position;
			enemyPosition.x += cellScale.width / 2;
			enemyPosition.y += cellScale.height / 2;

			Position playerPosition = player->transform.position;
			playerPosition.x += cellScale.width / 2;
			playerPosition.y += cellScale.height / 2;

			wMecro::DrawLine(hdc, enemyPosition, playerPosition, 3, W_RED);
		}
	}
	wMecro::DrawObject(hdc, coins);
	wMecro::DrawObject(hdc, player);
	wMecro::DrawObject(hdc, enemys);
	for (int i = (int)enemys.size() - 1; i >= 0; i--)
	{
		wMecro::DrawObject(hdc, enemys[i]);

		if (enemys[i]->GetDebug() != debug)
			enemys[i]->SetDebug(debug);

		if (enemys[i]->DetectedPlayer(this))
			enemys[i]->SetDebug(false);
	}
}

void PacMan::CheckCoin()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i])
		{
			Position coinGridPosition = ConvertPositionToGridPosition(coins[i]->transform.position);
			if (coinGridPosition == player->GetGridPosition())
				Delete(coins[i]);
		}
	}
}

bool PacMan::CheckPlayerPath(int map)
{
	if (map != WALL && map != DOOR)
		return true;

	return false;
}

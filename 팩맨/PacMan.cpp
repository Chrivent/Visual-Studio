#include "PacMan.h"

PacMan::PacMan(int clientWidth, int clientHeight)
{
	map = new int* [HEIGHT];
	for (int y = 0; y < HEIGHT; y++)
	{
		map[y] = new int[WIDTH];

		for (int x = 0; x < WIDTH; x++)
			map[y][x] = mapData[y][x];
	}

	this->cellWidth = clientWidth / WIDTH;
	this->cellHeight = clientHeight / HEIGHT;

	debug = true;

	int portalIndex = 0;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == PLAYER)
			{
				player = new Player;
				player->transform.position = { x * cellWidth, y * cellHeight };
				player->transform.scale = { cellWidth, cellHeight };

				playerDirection = player->direction;
				playerX = player->transform.position.x / cellWidth;
				playerY = player->transform.position.y / cellHeight;
				playerTargetX = playerX;
				playerTargetY = playerY;
			}

			if (map[y][x] == WALL)
			{
				Wall* wall = new Wall;
				wall->transform.position = { x * cellWidth, y * cellHeight };
				wall->transform.scale = { cellWidth, cellHeight };
				walls.push_back(wall);
			}
			else
			{
				Path* path = new Path;
				path->transform.position = { x * cellWidth, y * cellHeight };
				path->transform.scale = { cellWidth, cellHeight };
				paths.push_back(path);
			}
			
			if (map[y][x] == COIN)
			{
				Coin* coin = new Coin;
				coin->transform.position = { x * cellWidth, y * cellHeight };
				coin->transform.scale = { cellWidth, cellHeight };
				coins.push_back(coin);
			}
			
			if (map[y][x] == ENEMY)
			{
				enemyCount++;

				Enemy* enemy = new Enemy;
				enemy->transform.position = { x * cellWidth, y * cellHeight };
				enemy->transform.scale = { cellWidth, cellHeight };
				enemy->id = enemyCount;
				enemys.push_back(enemy);

				enemyTargetPositions.push_back(enemy->transform.position);
				enemyEndXs.push_back(playerX);
				enemyEndYs.push_back(playerY);
				enemyFindPaths.push_back(false);
				enemyXs.push_back(enemy->transform.position.x / cellWidth);
				enemyYs.push_back(enemy->transform.position.y / cellHeight);

				AStar* aStar = new AStar(map, WIDTH, HEIGHT);
				aStar->debug = debug;
				enemyAStars.push_back(aStar);
			}
		}
	}
}

PacMan::~PacMan()
{
	Delete(player);
	Delete(walls);
	Delete(coins);
	Delete(enemys);
	Delete(paths);
	if (map)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(map[y]);
		Delete(map);
	}
}

void PacMan::PlayerGaspUpdate()
{
	player->Gasp();
}

void PacMan::PlayerMoveUpdate()
{
	int errorX = player->transform.position.x % cellWidth;
	int errorY = player->transform.position.y % cellHeight;

	if (errorX < playerSpeed && errorY < playerSpeed)
	{
		player->direction = playerDirection;

		playerX = player->transform.position.x / cellWidth;
		playerY = player->transform.position.y / cellHeight;

		player->transform.position.x = playerX * cellWidth;
		player->transform.position.y = playerY * cellHeight;

		CheckCoin();
	}

	switch (player->direction)
	{
	case Left:
		if (player->transform.position.x <= 0)
		{
			player->transform.position.x = cellWidth * WIDTH;
			playerX = player->transform.position.x / cellWidth;
		}

		if (map[playerY][playerX - 1] != WALL)
		{
			player->transform.MoveLeft(playerSpeed);
			player->moving = true;
			playerTargetX = playerX - 1;
		}
		else
			player->moving = false;
		break;

	case Right:
		if (player->transform.position.x >= cellWidth * (WIDTH - 1))
		{
			player->transform.position.x = 0;
			playerX = player->transform.position.x / cellWidth;
		}

		if (map[playerY][playerX + 1] != WALL)
		{
			player->transform.MoveRight(playerSpeed);
			player->moving = true;
			playerTargetX = playerX + 1;
		}
		else
			player->moving = false;
		break;

	case Up:
		if (player->transform.position.y <= 0)
		{
			player->transform.position.y = cellHeight * HEIGHT;
			playerY = player->transform.position.y / cellHeight;
		}

		if (player->transform.position.y > 0 && map[playerY - 1][playerX] != WALL)
		{
			player->transform.MoveUp(playerSpeed);
			player->moving = true;
			playerTargetY = playerY - 1;
		}
		else
			player->moving = false;
		break;

	case Down:
		if (player->transform.position.y >= cellHeight * (HEIGHT - 1))
		{
			player->transform.position.y = 0;
			playerY = player->transform.position.y / cellHeight;
		}

		if (player->transform.position.y <= cellHeight * HEIGHT && map[playerY + 1][playerX] != WALL)
		{
			player->transform.MoveDown(playerSpeed);
			player->moving = true;
			playerTargetY = playerY + 1;
		}
		else
			player->moving = false;
		break;
	}
}

void PacMan::EnemyMoveUpdate()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		int errorX = enemys[i]->transform.position.x % cellWidth;
		int errorY = enemys[i]->transform.position.y % cellHeight;

		if (errorX < enemySpeed && errorY < enemySpeed)
		{
			enemyXs[i] = enemys[i]->transform.position.x / cellWidth;
			enemyYs[i] = enemys[i]->transform.position.y / cellHeight;

			enemys[i]->transform.position.x = enemyXs[i] * cellWidth;
			enemys[i]->transform.position.y = enemyYs[i] * cellHeight;

			enemyAStars[i]->ClearPath(paths);
		}

		enemys[i]->transform.MoveTo(enemyTargetPositions[i], enemySpeed);

		if (enemyAStars[i]->pathPoses.empty())
		{
			enemyFindPaths[i] = enemyAStars[i]->FindPath({ enemyXs[i], enemyYs[i] }, { playerX, playerY }, paths, cellWidth, cellHeight);
			enemyEndXs[i] = playerX;
			enemyEndYs[i] = playerY;
		}

		if (!enemyAStars[i]->pathPoses.empty())
		{
			Position pos = enemyAStars[i]->pathPoses.top();
			enemyTargetPositions[i] = { pos.x * cellWidth + 1, pos.y * cellHeight + 1 };

			if (pos.x == enemyXs[i] && pos.y == enemyYs[i])
				enemyAStars[i]->pathPoses.pop();
		}
	}
}

void PacMan::SetPlayerDirection(Direction direction)
{
	bool canSet = false;

	switch (direction)
	{
	case Left:
		if (map[playerTargetY][playerTargetX - 1] != WALL)
			canSet = true;
		break;

	case Right:
		if (map[playerTargetY][playerTargetX + 1] != WALL)
			canSet = true;
		break;

	case Up:
		if (map[playerTargetY - 1][playerTargetX] != WALL)
			canSet = true;
		break;

	case Down:
		if (map[playerTargetY + 1][playerTargetX] != WALL)
			canSet = true;
		break;
	}

	if (canSet)
		playerDirection = direction;
}

void PacMan::Draw(HDC hdc, HWND hWnd)
{
	wMecro::DrawRectangle(hdc, wMecro::GetClientTransform(hWnd), W_BLACK);
	wMecro::DrawObject(hdc, walls);
	wMecro::DrawObject(hdc, paths);
	wMecro::DrawObject(hdc, coins);
	wMecro::DrawObject(hdc, player);
	wMecro::DrawObject(hdc, enemys);
	if (debug)
	{
		for (int i = 0; i < enemys.size(); i++)
		{
			Position enemyPos = enemys[i]->transform.position;
			enemyPos.x += cellWidth / 2;
			enemyPos.y += cellHeight / 2;

			Position playerPos = player->transform.position;
			playerPos.x += cellWidth / 2;
			playerPos.y += cellHeight / 2;

			wMecro::DrawLine(hdc, enemyPos, playerPos, 3, W_RED);
		}
	}
}

void PacMan::CheckCoin()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i] != nullptr)
		{
			int coinX = coins[i]->transform.position.x / cellWidth;
			int coinY = coins[i]->transform.position.y / cellHeight;

			if (coinX == playerX && coinY == playerY)
				Delete(coins[i]);
		}
	}
}

#include "Pacman.h"

Pacman::Pacman(Scale clientScale)
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

	InitParameter();

	debug = true;

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			const Position position = ConvertGridPositionToPosition({ x, y });

			if (maps[y][x] == WALL)
			{
				Wall* wall = new Wall;
				wall->transform.position = position;
				wall->transform.scale = cellScale;
				walls.push_back(wall);
			}

			if (maps[y][x] == DOOR)
			{
				Door* door = new Door;
				door->transform.position = position;
				door->transform.scale = cellScale;
				doors.push_back(door);
			}
		}
	}

	InitEntity();

	scoreTextTransform.position = { 0, cellScale.height * HEIGHT };
	scoreTextTransform.scale = cellScale;
	scoreTextTransform.scale.width /= 3;
	scoreTextTransform.scale.width *= 2;

	gameClearTextTransform.position = { cellScale.width * WIDTH / 40 * 9, cellScale.height * HEIGHT / 5 * 2 };
	gameClearTextTransform.scale = cellScale;
	gameClearTextTransform.scale.width *= 2;
	gameClearTextTransform.scale.height *= 3;
}

Pacman::~Pacman()
{
	DeleteEntity();
	Delete(walls);
	Delete(doors);
	if (maps)
	{
		for (int y = 0; y < HEIGHT; y++)
			Delete(maps[y]);
		Delete(maps);
	}
}

void Pacman::InitParameter()
{
	doorOpenCount = 0;
	doorOpenTime = 300;
	doorOpenTimer = 0;
	enemyHunted = false;
	score = 0;
	gameOver = false;
	gameClear = false;
}

void Pacman::InitEntity()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			const Position position = ConvertGridPositionToPosition({ x, y });

			if (maps[y][x] == COIN)
			{
				Coin* coin = new Coin(Small);
				coin->transform.position = position;
				coin->transform.scale = cellScale;
				coins.push_back(coin);
			}

			if (maps[y][x] == BIG_COIN)
			{
				Coin* coin = new Coin(Big);
				coin->transform.position = position;
				coin->transform.scale = cellScale;
				coins.push_back(coin);
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
				enemies.push_back(enemy);
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		vector<Path*> tmpPaths;
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				const Position position = ConvertGridPositionToPosition({ x, y });

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

	inputDirection = player->GetDirection();
	player->SetGridPosition(ConvertPositionToGridPosition(player->transform.position, 0));
	player->SetTargetGridPosition(player->GetGridPosition());

	bool lookUp = true;
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->SetDirection(lookUp ? Up : Down);
		enemies[i]->SetIndex(i);
		const Position gridPosition = ConvertPositionToGridPosition(enemies[i]->transform.position, 0);
		enemies[i]->SetGridPosition(gridPosition);
		enemies[i]->SetTargetGridPosition(gridPosition);
		enemies[i]->SetEndGridPosition(gridPosition);
		enemies[i]->SetStartGridPosition(gridPosition);

		enemies[i]->GetAStar()->SetDebug(debug, paths[i]);
		enemies[i]->SetStayPositions(enemies[i]->transform.position, cellScale);

		for (int j = 0; j < paths[i].size(); j++)
			paths[i][j]->SetIndex(i);

		lookUp = !lookUp;
	}
}

void Pacman::DeleteEntity()
{
	Delete(player);
	Delete(coins);
	Delete(enemies);
	for (int i = 0; i < enemies.size(); i++)
		Delete(paths[i]);

	coins.clear();
	enemies.clear();
	for (int i = 0; i < enemies.size(); i++)
		paths[i].clear();
	paths.clear();
}

void Pacman::PlayerMoveUpdate()
{
	player->Move(this);
}

void Pacman::PlayerGaspUpdate() const
{
	player->Gasp();
}

void Pacman::EnemyMoveUpdate()
{
	if (!gameOver)
	{
		for (Enemy*& enemy : enemies)
			enemy->Move(this);

		if (doorOpenTimer < doorOpenTime)
			doorOpenTimer++;
		else if (doorOpenCount <= enemies.size())
		{
			doorOpenCount++;
			doorOpenTimer = 0;
		}
	}
}

void Pacman::EnemyStepUpdate() const
{
	for (Enemy* enemy : enemies)
		enemy->Step();
}

void Pacman::SetInputDirection(Direction direction)
{
	bool canSet = false;

	switch (direction)
	{
	case Left:
		if (player->GridPositionIsPath({ player->GetTargetGridPosition().x - 1, player->GetTargetGridPosition().y }, this))
			canSet = true;
		break;

	case Right:
		if (player->GridPositionIsPath({ player->GetTargetGridPosition().x + 1, player->GetTargetGridPosition().y }, this))
			canSet = true;
		break;

	case Up:
		if (player->GridPositionIsPath({ player->GetTargetGridPosition().x, player->GetTargetGridPosition().y - 1 }, this))
			canSet = true;
		break;

	case Down:
		if (player->GridPositionIsPath({ player->GetTargetGridPosition().x, player->GetTargetGridPosition().y + 1 }, this))
			canSet = true;
		break;
	}

	if (canSet)
		inputDirection = direction;
}

void Pacman::AddScore(int score)
{
	this->score += score;
}

void Pacman::ResetAllHuntedTimer() const
{
	for (Enemy* enemy : enemies)
		enemy->ResetHuntedTimer();
}

void Pacman::GameOver()
{
	gameOver = true;
}

void Pacman::ResetGame()
{
	DeleteEntity();
	InitParameter();
	InitEntity();
}

void Pacman::GameClear()
{
	Delete(enemies);
	enemies.clear();

	gameClear = true;
}

bool Pacman::AllEnemyIsHunted() const
{
	for (const Enemy* enemy : enemies)
	{
		if (!enemy->GetHunted())
			return false;
	}

	return true;
}

Position Pacman::ConvertPositionToGridPosition(Position position, int speed) const
{
	Position gridPosition;

	gridPosition.x = (position.x + speed) / cellScale.width;
	gridPosition.y = (position.y + speed) / cellScale.height;

	return gridPosition;
}

Position Pacman::ConvertGridPositionToPosition(Position gridPosition) const
{
	Position position;

	position.x = gridPosition.x * cellScale.width;
	position.y = gridPosition.y * cellScale.height;

	return position;
}

void Pacman::Draw(HDC hdc, HWND hWnd)
{
	DrawRectangle(hdc, wMecro::GetClientTransform(hWnd), W_BLACK);
	DrawObject(hdc, walls);
	if (!gameOver)
	{
		for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; i--)
		{
			DrawObject(hdc, paths[i]);

			AStar* aStar = enemies[i]->GetAStar();
			if (aStar->GetDebug() != debug)
				aStar->SetDebug(debug, paths[i]);
		}
	}
	DrawObject(hdc, doors);
	if (!gameOver)
	{
		for (Enemy*& enemy : enemies)
		{
			if (debug && enemy->DetectedPlayer(this) && enemy->GetHunter())
			{
				Position enemyPosition = enemy->transform.position;
				enemyPosition.x += cellScale.width / 2;
				enemyPosition.y += cellScale.height / 2;

				Position playerPosition = player->transform.position;
				playerPosition.x += cellScale.width / 2;
				playerPosition.y += cellScale.height / 2;

				wMecro::DrawLine(hdc, enemyPosition, playerPosition, 3, W_RED);
			}
		}
	}
	DrawObject(hdc, coins);
	DrawObject(hdc, player);
	if (!player->IsFallDown())
	{
		for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; i--)
		{
			DrawObject(hdc, enemies[i]);

			if (enemies[i]->GetDebug() != debug)
				enemies[i]->SetDebug(debug);

			if (enemies[i]->DetectedPlayer(this))
				enemies[i]->SetDebug(false);
		}
	}
	const wstring scoreStr = std::to_wstring(score);
	DrawTextOut(hdc, scoreTextTransform, scoreStr.c_str(), W_WHITE);
	if (gameClear)
		DrawTextOut(hdc, gameClearTextTransform, TEXT("Clear!"), W_WHITE);
}

#include "Player.h"
#include "Pacman.h"

Player::Player()
{
	speed = 3;
	originSpeed = 3;
	gaspIndex = 0;
	gaspOpening = false;
	direction = Left;
	moving = true;
	deadTime = 200;
	deadTimer = 0;
}

void Player::Draw(HDC hdc)
{
	int directionOffset;
	switch (direction)
	{
	case Left:
		directionOffset = 1;
		break;
	case Right:
		directionOffset = 0;
		break;
	case Up:
		directionOffset = 2;
		break;
	case Down:
		directionOffset = 3;
		break;
	}

	if (!deadTimer)
		DrawBitmapPartTransparent(hdc, transform, TEXT("pacman.bmp"), 14, 4, (gaspIndex == 2 ? 0 : 14 * directionOffset) + gaspIndex, W_BLACK);
	else
	{
		if (deadTimer < deadTime / 2)
			DrawBitmapPartTransparent(hdc, transform, TEXT("pacman.bmp"), 14, 4, (gaspIndex == 2 ? 0 : 14 * directionOffset) + gaspIndex, W_BLACK);
		else
		{
			int index = 3 + (deadTimer - deadTime / 2) / (deadTime / 36);
			if (index > 13)
				index = 16;
			DrawBitmapPartTransparent(hdc, transform, TEXT("pacman.bmp"), 14, 4, index, W_BLACK);
		}
	}
}

void Player::Gasp()
{
	if (!deadTimer)
	{
		if (moving)
		{
			if (!gaspOpening)
			{
				gaspIndex++;
				if (gaspIndex == 2)
					gaspOpening = true;
			}
			else
			{
				gaspIndex--;
				if (gaspIndex == 0)
					gaspOpening = false;
			}
		}
		else
			gaspIndex = 1;
	}
}

void Player::Move(Pacman* pacman)
{
	if (!pacman->GetGameOver())
	{
		const Scale cellScale = pacman->GetCellScale();

		const int errorX = (transform.position.x + speed - 1) % cellScale.width;
		const int errorY = (transform.position.y + speed - 1) % cellScale.height;
		const int toleranceRange = (speed - 1) * 2;

		if (errorX <= toleranceRange && errorY <= toleranceRange)
		{
			direction = pacman->GetInputDirection();

			gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
			transform.position = pacman->ConvertGridPositionToPosition(gridPosition);

			CheckCoin(pacman);
		}

		CheckEnemy(pacman);

		switch (direction)
		{
		case Left:
			if (transform.position.x <= 0)
			{
				transform.position.x = cellScale.width * (WIDTH - 1);
				gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
			}

			if (GridPositionIsPath({ gridPosition.x - 1, gridPosition.y }, pacman))
			{
				transform.MoveLeft(speed);
				moving = true;
				targetGridPosition = gridPosition;
				targetGridPosition.x--;
			}
			else
				moving = false;
			break;

		case Right:
			if (transform.position.x >= cellScale.width * (WIDTH - 1))
			{
				transform.position.x = 0;
				gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
			}

			if (GridPositionIsPath({ gridPosition.x + 1, gridPosition.y }, pacman))
			{
				transform.MoveRight(speed);
				moving = true;
				targetGridPosition = gridPosition;
				targetGridPosition.x++;
			}
			else
				moving = false;
			break;

		case Up:
			if (transform.position.y <= 0)
			{
				transform.position.y = cellScale.height * (HEIGHT - 1);
				gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
			}

			if (GridPositionIsPath({ gridPosition.x, gridPosition.y - 1 }, pacman))
			{
				transform.MoveUp(speed);
				moving = true;
				targetGridPosition = gridPosition;
				targetGridPosition.y--;
			}
			else
				moving = false;
			break;

		case Down:
			if (transform.position.y >= cellScale.height * (HEIGHT - 1))
			{
				transform.position.y = 0;
				gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
			}

			if (GridPositionIsPath({ gridPosition.x, gridPosition.y + 1 }, pacman))
			{
				transform.MoveDown(speed);
				moving = true;
				targetGridPosition = gridPosition;
				targetGridPosition.y++;
			}
			else
				moving = false;
			break;
		}

		if (pacman->GetCoins().empty())
			pacman->GameClear();
	}
	else
	{
		if (deadTimer < deadTime)
			deadTimer++;
		else
			pacman->ResetGame();
	}
}

bool Player::GridPositionIsPath(Position gridPosition, const Pacman* pacman)
{
	const int map = pacman->GetMaps()[gridPosition.y][gridPosition.x];

	if (map != WALL &&
		map != DOOR &&
		map != TRANSPARENT_WALL)
		return true;

	return false;
}

void Player::CheckCoin(Pacman* pacman) const
{
	vector<Coin*>& coins = pacman->GetCoins();
	
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i])
		{
			Position coinGridPosition = pacman->ConvertPositionToGridPosition(coins[i]->transform.position, 0);
			if (coinGridPosition == GetGridPosition())
			{
				if (coins[i]->GetType() == Big)
					pacman->SetEnemyHunted(true);

				pacman->AddScore(coins[i]->GetScore());
				Delete(coins[i]);
				coins.erase(coins.begin() + i);
				break;
			}
		}
	}
}

void Player::CheckEnemy(Pacman* pacman) const
{
	const vector<Enemy*> enemies = pacman->GetEnemies();
	const Scale cellScale = pacman->GetCellScale();

	for (const Enemy* enemy : enemies)
	{
		if (enemy->GetHunter())
		{
			const int distanceX = abs(enemy->transform.position.x - transform.position.x);
			const int distanceY = abs(enemy->transform.position.y - transform.position.y);

			if (distanceX <= cellScale.width / 2 && distanceY <= cellScale.height / 2)
				pacman->GameOver();
		}
	}
}

bool Player::IsFallDown() const
{
	return deadTimer >= deadTime / 2;
}


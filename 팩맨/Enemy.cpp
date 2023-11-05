#include "Enemy.h"
#include "Pacman.h"
#include "InBox.h"

Enemy::Enemy()
{
	index = 0;
	speed = 3;
	originSpeed = 3;
	direction = Up;
	detectRange = 5;
	stepOrigin = true;
	randFlag = true;
	hunter = false;
	hunted = false;
	huntedTime = 500;
	huntedTimer = 0;
	huntedSpeedRate = 0.7f;
	eaten = false;
	eatenSpeedRate = 2.8f;
	sparkle = false;
	sparkleTime = 10;
	sparkleTimer = 0;
	score = 200;

	aStar = new AStar;
	state = &InBox::Instance();

	debug = false;
}

Enemy::~Enemy()
{
	Delete(aStar);
}

void Enemy::Draw(HDC hdc)
{
	if (!hunted)
	{
		int directionOffset;
		switch (direction)
		{
		case Left:
			directionOffset = 2;
			break;
		case Right:
			directionOffset = 0;
			break;
		case Up:
			directionOffset = 4;
			break;
		case Down:
			directionOffset = 6;
			break;
		}

		if (!eaten)
			DrawBitmapPartTransparent(hdc, transform, TEXT("ghost.bmp"), 12, 12, 12 * (index % 12) + (stepOrigin ? 0 : 1) + directionOffset, RGB(109, 109, 109));
		else
			DrawBitmapPartTransparent(hdc, transform, TEXT("ghost.bmp"), 12, 12, 20 + directionOffset / 2, RGB(109, 109, 109));

		if (debug && hunter)
		{
			Position debugPosition = transform.position;
			debugPosition.x += (transform.scale.width / 2) * (1 - detectRange * 2);
			debugPosition.y += (transform.scale.height / 2) * (1 - detectRange * 2);

			Scale debugScale = transform.scale;
			debugScale.width *= detectRange * 2;
			debugScale.height *= detectRange * 2;

			wMecro::Transform debugTransform;
			debugTransform.position = debugPosition;
			debugTransform.scale = debugScale;

			DrawRectangleEmpty(hdc, debugTransform, 1, W_SKYBLUE);
		}
	}
	else
		DrawBitmapPartTransparent(hdc, transform, TEXT("ghost.bmp"), 12, 12, 8 + (stepOrigin ? 0 : 1) + (sparkle ? 2 : 0), RGB(109, 109, 109));
}

void Enemy::Step()
{
	stepOrigin = !stepOrigin;
}

void Enemy::Move(Pacman* pacman)
{
	state->Update(this, pacman);
}

void Enemy::SetStayPositions(Position startPosition, Scale cellScale)
{
	stayPositions[0] = startPosition;
	stayPositions[1] = startPosition;

	const int offset = cellScale.height / 2;
	stayPositions[0].y += offset;
	stayPositions[1].y -= offset;
}

void Enemy::MoveInBox(Pacman* pacman)
{
	if (abs(stayPositions[1].y - transform.position.y) < speed)
		direction = Down;

	if (abs(stayPositions[0].y - transform.position.y) < speed)
		direction = Up;

	if (direction == Up)
		transform.MoveTo(stayPositions[1], speed);
	else
		transform.MoveTo(stayPositions[0], speed);

	if (pacman->GetEnemyHunted())
	{
		hunted = true;

		if (pacman->AllEnemyIsHunted())
			pacman->SetEnemyHunted(false);
	}

	if (hunted)
	{
		if (huntedTimer < huntedTime)
		{
			Sparkle();
			huntedTimer++;
		}
		else
		{
			hunted = false;
			huntedTimer = 0;
		}
	}
}

void Enemy::MoveHunter(Pacman* pacman)
{
	GridUpdateEvent(pacman);

	if (aStar->GetPathGridPositions().empty())
	{
		if (DetectedPlayer(pacman))
		{
			endGridPosition = pacman->GetPlayer()->GetGridPosition();
			randFlag = true;
		}
		else
		{
			if (gridPosition == endGridPosition)
				randFlag = true;

			if (randFlag)
			{
				do
				{
					endGridPosition.x = RandNum(0, WIDTH);
					endGridPosition.y = RandNum(0, HEIGHT);
				} while (!GridPositionIsPath(endGridPosition, pacman));
				randFlag = false;
			}
		}

		aStar->FindPath(gridPosition, endGridPosition, this, pacman);
	}

	AStarMoveEvent(pacman);
}

void Enemy::MoveHunted(Pacman* pacman)
{
	if (pacman->GetEnemyHunted())
	{
		pacman->ResetAllHuntedTimer();
		pacman->SetEnemyHunted(false);
	}

	if (huntedTimer < huntedTime)
	{
		Sparkle();
		GridUpdateEvent(pacman);

		if (aStar->GetPathGridPositions().empty())
		{
			if (gridPosition == endGridPosition)
				randFlag = true;

			if (randFlag || GridPositionIsAroundPlayer(endGridPosition, pacman))
			{
				do
				{
					endGridPosition.x = RandNum(0, WIDTH);
					endGridPosition.y = RandNum(0, HEIGHT);
				} while (!GridPositionIsPath(endGridPosition, pacman));
				randFlag = false;
			}

			aStar->FindPath(gridPosition, endGridPosition, this, pacman);
		}

		AStarMoveEvent(pacman);

		const Position playerPosition = pacman->GetPlayer()->transform.position;
		const int distanceX = abs(playerPosition.x - transform.position.x);
		const int distanceY = abs(playerPosition.y - transform.position.y);
		const Scale cellScale = pacman->GetCellScale();

		if (distanceX < cellScale.width / 2 && distanceY < cellScale.height / 2)
		{
			eaten = true;
			pacman->AddScore(score);
		}

		huntedTimer++;
	}
	else
	{
		hunted = false;
		huntedTimer = 0;
	}
}

void Enemy::MoveEaten(Pacman* pacman)
{
	GridUpdateEvent(pacman);

	if (aStar->GetPathGridPositions().empty())
	{
		if (gridPosition == startGridPosition)
			eaten = false;

		aStar->FindPath(gridPosition, startGridPosition, this, pacman);
	}

	AStarMoveEvent(pacman);
}

void Enemy::ResetHuntedTimer()
{
	huntedTimer = 0;
}

void Enemy::GridUpdateEvent(Pacman* pacman)
{
	const Scale cellScale = pacman->GetCellScale();
	const vector<Path*> paths = pacman->GetPaths()[index];

	const int errorX = (transform.position.x + speed - 1) % cellScale.width;
	const int errorY = (transform.position.y + speed - 1) % cellScale.height;
	const int toleranceRange = (speed - 1) * 2;

	if (errorX <= toleranceRange && errorY <= toleranceRange)
	{
		gridPosition = pacman->ConvertPositionToGridPosition(transform.position, speed);
		transform.position = pacman->ConvertGridPositionToPosition(gridPosition);

		aStar->ClearPath(paths);
	}
	else
	{
		const Position targetPosition = pacman->ConvertGridPositionToPosition(targetGridPosition);

		const int distanceX = targetPosition.x - transform.position.x;
		const int distanceY = targetPosition.y - transform.position.y;

		if (abs(distanceX) > abs(distanceY))
			direction = distanceX > 0 ? Right : Left;
		else
			direction = distanceY > 0 ? Down : Up;
	}
}

void Enemy::AStarMoveEvent(const Pacman* pacman)
{
	transform.MoveTo(pacman->ConvertGridPositionToPosition(targetGridPosition), speed);

	if (!aStar->GetPathGridPositions().empty())
	{
		Position pathGridPosition = aStar->GetPathGridPositions().top();
		targetGridPosition = pathGridPosition;

		if (pathGridPosition == gridPosition)
			aStar->GetPathGridPositions().pop();
	}
}

void Enemy::ChangeState(State* state, Pacman* pacman)
{
	this->state->Exit(this, pacman);
	this->state = state;
	this->state->Start(this, pacman);
}

void Enemy::Sparkle()
{
	if (huntedTimer >= (huntedTime / 5) * 4)
	{
		if (sparkleTimer < sparkleTime)
			sparkleTimer++;
		else
		{
			sparkle = !sparkle;
			sparkleTimer = 0;
		}
	}
	else
		sparkle = false;
}

bool Enemy::DetectedPlayer(const Pacman* pacman) const
{
	return GridPositionIsAroundPlayer(gridPosition, pacman);
}

bool Enemy::GridPositionIsPath(Position gridPosition, const Pacman* pacman)
{
	const int map = pacman->GetMaps()[gridPosition.y][gridPosition.x];

	if (gridPosition.x >= 0 &&
		gridPosition.x < WIDTH &&
		gridPosition.y >= 0 &&
		gridPosition.y < HEIGHT &&
		map != WALL &&
		map != TRANSPARENT_WALL)
		return true;

	return false;
}

bool Enemy::GridPositionIsAroundPlayer(Position gridPosition, const Pacman* pacman) const
{
	const int distanceX = abs(pacman->GetPlayer()->GetGridPosition().x - gridPosition.x);
	const int distanceY = abs(pacman->GetPlayer()->GetGridPosition().y - gridPosition.y);

	if (distanceX <= detectRange && distanceY <= detectRange)
		return true;

	return false;
}

#include "Enemy.h"
#include "PacMan.h"
#include "InBox.h"

Enemy::Enemy()
{
	direction = Up;
	detectRange = 5;
	randFlag = true;

	state = &InBox::Instance();
}

Enemy::~Enemy()
{
	Delete(aStar);
}

void Enemy::Draw(HDC hdc)
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

	wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("ghost.bmp"), 12, 12, 12 * (index % 12) + (stepOrigin ? 0 : 1) + directionOffset, RGB(109, 109, 109));

	if (debug)
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

		wMecro::DrawRectangleEmpty(hdc, debugTransform, 1, W_SKYBLUE);
	}
}

void Enemy::Step()
{
	stepOrigin = !stepOrigin;
}

void Enemy::CreateAStar(int** maps)
{
	aStar = new AStar(maps);
}

void Enemy::Update(PacMan* pacMan)
{
	state->Update(this, pacMan);
}

void Enemy::SetStayPositions(Position startPosition, Scale cellScale)
{
	stayPositions[0] = startPosition;
	stayPositions[1] = startPosition;

	int offset = cellScale.height / 2;
	stayPositions[0].y += offset;
	stayPositions[1].y -= offset;
}

void Enemy::MoveStay(int distance)
{
	if (abs(stayPositions[1].y - transform.position.y) < distance)
		direction = Down;

	if (abs(stayPositions[0].y - transform.position.y) < distance)
		direction = Up;

	if (direction == Up)
		transform.MoveTo(stayPositions[1], distance);
	else
		transform.MoveTo(stayPositions[0], distance);
}

bool Enemy::DetectedPlayer(PacMan* pacMan)
{
	int distanceX = abs(gridPosition.x - pacMan->GetPlayer()->GetGridPosition().x);
	int distanceY = abs(gridPosition.y - pacMan->GetPlayer()->GetGridPosition().y);

	if (distanceX < detectRange && distanceY < detectRange)
		return true;

	return false;
}

#pragma once

#include "mecro.h"

enum Direction
{
	None,
	Left,
	Right,
	Up,
	Down
};

class GridObject : public wMecro::Object
{
public:
	void SetDirection(Direction direction) { this->direction = direction; }
	void SetGridPosition(Position gridPosition) { this->gridPosition = gridPosition; }
	void SetTargetGridPosition(Position targetGridPosition) { this->targetGridPosition = targetGridPosition; }

	Direction GetDirection() const { return direction; }
	Position GetGridPosition() const { return gridPosition; }
	Position GetTargetGridPosition() const { return targetGridPosition; }

	void ChangeSpeed(float speedRate);
	void ResetSpeed();

protected:
	Direction direction;
	Position gridPosition;
	Position targetGridPosition;
	int speed;
	int originSpeed;
};


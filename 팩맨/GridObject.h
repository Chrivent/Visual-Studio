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

	Direction GetDirection() { return direction; }
	Position GetGridPosition() { return gridPosition; }

protected:
	Direction direction;
	Position gridPosition;
};


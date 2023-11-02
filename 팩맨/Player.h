#pragma once

#include "GridObject.h"

class Player : public GridObject
{
public:
	Player();

	virtual void Draw(HDC hdc) override;

	void SetMoving(bool moving) { this->moving = moving; }
	void SetTargetGridPosition(Position targetGridPosition) { this->targetGridPosition = targetGridPosition; }

	Position GetTargetGridPosition() { return targetGridPosition; }

	void Gasp();

private:
	bool moving;

	Position targetGridPosition;

	int gaspIndex;
	bool gaspOpening;
};


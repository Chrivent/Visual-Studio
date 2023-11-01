#pragma once

#include "mecro.h"

enum Direction
{
	Left,
	Right,
	Up,
	Down
};

class Player : public wMecro::Object
{
public:
	Player();

	virtual void Draw(HDC hdc) override;

	void Gasp();

	Direction direction;
	bool moving;

private:
	int gaspIndex;
	bool gaspOpening;
};


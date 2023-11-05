#pragma once

#include "GridObject.h"

class Pacman;

class Player : public GridObject
{
public:
	Player();

	void Draw(HDC hdc) override;

	void SetMoving(bool moving) { this->moving = moving; }

	void Gasp();
	void Move(Pacman* pacman);
	static bool GridPositionIsPath(Position gridPosition, const Pacman* pacman);
	void CheckCoin(Pacman* pacman) const;
	void CheckEnemy(Pacman* pacman) const;
	bool IsFallDown() const;

private:
	bool moving;

	int gaspIndex;
	bool gaspOpening;
	int deadTime;
	int deadTimer;
};


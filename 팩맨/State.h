#pragma once

class Enemy;
class PacMan;

__interface State
{
	virtual void Update(Enemy* enemy, PacMan* pacMan) = 0;
};

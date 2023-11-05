#pragma once

class Enemy;
class Pacman;

__interface State
{
	virtual void Start(Enemy* enemy, Pacman* pacman) = 0;
	virtual void Update(Enemy* enemy, Pacman* pacman) = 0;
	virtual void Exit(Enemy* enemy, Pacman* pacman) = 0;
};

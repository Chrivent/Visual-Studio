#pragma once

#include "State.h"

class Eaten : public State
{
public:
	static Eaten& Instance();

	void Start(Enemy* enemy, Pacman* pacman) override;
	void Update(Enemy* enemy, Pacman* pacman) override;
	void Exit(Enemy* enemy, Pacman* pacman) override;
};


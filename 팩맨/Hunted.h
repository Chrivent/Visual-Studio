#pragma once

#include "State.h"

class Hunted : public State
{
public:
	static Hunted& Instance();

	void Start(Enemy* enemy, Pacman* pacman) override;
	void Update(Enemy* enemy, Pacman* pacman) override;
	void Exit(Enemy* enemy, Pacman* pacman) override;
};


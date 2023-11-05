#pragma once

#include "State.h"

class Hunter : public State
{
public:
	static Hunter& Instance();

	void Start(Enemy* enemy, Pacman* pacman) override;
	void Update(Enemy* enemy, Pacman* pacman) override;
	void Exit(Enemy* enemy, Pacman* pacman) override;
};


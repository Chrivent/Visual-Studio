#pragma once

#include "State.h"

class InBox : public State
{
public:
	static InBox& Instance();

	void Start(Enemy* enemy, Pacman* pacman) override;
	void Update(Enemy* enemy, Pacman* pacman) override;
	void Exit(Enemy* enemy, Pacman* pacman) override;
};


#pragma once

#include "State.h"

class InBox : public State
{
public:
	static InBox& Instance();

	virtual void Update(Enemy* enemy, PacMan* pacMan) override;
};


#pragma once

#include "State.h"

class Hunter : public State
{
public:
	static Hunter& Instance();

	virtual void Update(Enemy* enemy, PacMan* pacMan) override;
};


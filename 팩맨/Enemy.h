#pragma once

#include "mecro.h"
#include "Player.h"

class Enemy : public wMecro::Object
{
public:
	virtual void Draw(HDC hdc) override;

	int id;
	Direction direction;
};


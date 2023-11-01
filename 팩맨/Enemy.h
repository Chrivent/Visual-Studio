#pragma once

#include "mecro.h"

class Enemy : public wMecro::Object
{
public:
	virtual void Draw(HDC hdc) override;

	int id;
};


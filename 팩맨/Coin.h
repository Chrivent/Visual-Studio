#pragma once

#include "mecro.h"

class Coin : public wMecro::Object
{
public:
	virtual void Draw(HDC hdc) override;
};


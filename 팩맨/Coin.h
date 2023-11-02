#pragma once

#include "mecro.h"

enum Type
{
	Normal,
	Big
};

class Coin : public wMecro::Object
{
public:
	virtual void Draw(HDC hdc) override;
};


#pragma once

#include "mecro.h"

class Wall : public wMecro::Object
{
public:
	void Draw(HDC hdc) override;
};


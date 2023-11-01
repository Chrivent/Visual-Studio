#pragma once

#include "mecro.h"

class Wall : public wMecro::Object
{
public:
	virtual void Draw(HDC hdc) override;
};


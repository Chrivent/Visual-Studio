#pragma once

#include "mecro.h"

class Body : public Object
{
private:
	bool head;

public:
	Body();

	void ActivateHead();
	void Draw();
};
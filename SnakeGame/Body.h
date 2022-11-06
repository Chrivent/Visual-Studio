#pragma once

#include "util.h"

class Body : public Object
{
private:
	bool head;

public:
	Body();

	void ActivateHead();
	void Draw();
};
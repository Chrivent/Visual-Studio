#include "Body.h"

Body::Body()
{
	head = false;
}

void Body::ActivateHead()
{
	head = true;
}

void Body::Draw()
{
	DrawPoint(position.x, position.y, head ? "в├" : "бс", head ? C_HIGH_GREEN : C_SKY_BLUE);
}
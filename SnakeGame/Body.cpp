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
	DrawPoint(position.x, position.y, head ? "��" : "��", head ? C_HIGH_GREEN : C_SKY_BLUE);
}
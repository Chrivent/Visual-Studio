#include "GridObject.h"

void GridObject::ChangeSpeed(float speedRate)
{
	speed = static_cast<int>(speed * speedRate);
}

void GridObject::ResetSpeed()
{
	speed = originSpeed;
}

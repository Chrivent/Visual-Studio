#include "Door.h"

void Door::Draw(HDC hdc)
{
	Position position = transform.position;
	position.x += transform.scale.width / 4;
	position.y += transform.scale.height / 4;

	Scale scale = transform.scale;
	scale.width /= 2;
	scale.height /= 2;

	wMecro::Transform doorTransform;
	doorTransform.position = position;
	doorTransform.scale = scale;

	DrawRectangle(hdc, doorTransform, RGB(255, 128, 0));
}

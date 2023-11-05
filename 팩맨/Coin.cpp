#include "Coin.h"

Coin::Coin(Type type) : type(type)
{
	switch (type)
	{
	case Small:
		score = 10;
		break;
	case Big:
		score = 50;
		break;
	}

	sparkle = false;
	sparkleTime = 10;
	sparkleTimer = 0;
}

void Coin::Draw(HDC hdc)
{
	Position position = transform.position;
	Scale scale = transform.scale;

	switch (type)
	{
	case Small:
		position.x += transform.scale.width / 2 - transform.scale.width / 8;
		position.y += transform.scale.height / 2 - transform.scale.height / 8;

		scale.width /= 4;
		scale.height /= 4;
		break;

	case Big:
		position.x += transform.scale.width / 4;
		position.y += transform.scale.height / 4;

		scale.width /= 2;
		scale.height /= 2;
		break;
	}

	wMecro::Transform coinTransform;
	coinTransform.position = position;
	coinTransform.scale = scale;

	switch (type)
	{
	case Small:
		DrawEllipse(hdc, coinTransform, W_WHITE);
		break;
	case Big:
		Sparkle();
		if (sparkle)
			DrawEllipse(hdc, coinTransform, W_WHITE);
		break;
	}
}

void Coin::Sparkle()
{
	if (sparkleTimer < sparkleTime)
		sparkleTimer++;
	else
	{
		sparkle = !sparkle;
		sparkleTimer = 0;
	}
}

#include "Coin.h"

void Coin::Draw(HDC hdc)
{
	Position pos = transform.position;
	pos.x += transform.scale.width / 2 - transform.scale.width / 8;
	pos.y += transform.scale.height / 2 - transform.scale.height / 8;

	Scale sca = transform.scale;
	sca.width /= 4;
	sca.height /= 4;

	wMecro::Transform tra;
	tra.position = pos;
	tra.scale = sca;

	wMecro::DrawEllipse(hdc, tra, W_WHITE);
}

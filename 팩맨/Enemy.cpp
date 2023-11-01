#include "Enemy.h"

void Enemy::Draw(HDC hdc)
{
	wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("ghost.bmp"), 12, 12, 12 * id, W_BLACK);
}

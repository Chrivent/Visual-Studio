#include "Player.h"

Player::Player()
{
	gaspIndex = 0;
	gaspOpening = false;
	direction = Left;
	moving = true;
}

void Player::Draw(HDC hdc)
{
	switch (direction)
	{
	case Left:
		wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("pacmanLeft.bmp"), 3, 1, 2 - gaspIndex, W_WHITE);
		break;
	case Right:
		wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("pacmanRight.bmp"), 3, 1, gaspIndex, W_WHITE);
		break;
	case Up:
		wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("pacmanUp.bmp"), 1, 3, 2 - gaspIndex, W_WHITE);
		break;
	case Down:
		wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("pacmanDown.bmp"), 1, 3, gaspIndex, W_WHITE);
		break;
	}

	wMecro::DrawBitmapPartTransparent(hdc, transform, TEXT("pacman.bmp"), 3, 1, gaspIndex, W_WHITE);
}

void Player::Gasp()
{
	if (moving)
	{
		if (!gaspOpening)
		{
			gaspIndex++;
			if (gaspIndex == 2)
				gaspOpening = true;
		}
		else
		{
			gaspIndex--;
			if (gaspIndex == 0)
				gaspOpening = false;
		}
	}
	else
		gaspIndex = 1;
}

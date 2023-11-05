#pragma once

#include "mecro.h"

enum Type
{
	Small,
	Big
};

class Coin : public wMecro::Object
{
public:
	Coin(Type type);

	void Draw(HDC hdc) override;

	Type GetType() const { return type; }
	int GetScore() const { return score; }

	void Sparkle();

private:
	Type type;
	bool sparkle;
	int sparkleTime;
	int sparkleTimer;

	int score;
};


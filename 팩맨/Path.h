#pragma once

#include "mecro.h"

class Path : public wMecro::Object
{
public:
	Path();

	virtual void Draw(HDC hdc) override;

	bool debugVisit;
	bool debugToGo;

protected:
	virtual void DrawDebug(HDC hdc);
};


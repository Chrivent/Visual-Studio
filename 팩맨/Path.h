#pragma once

#include "mecro.h"

class Path : public wMecro::Object
{
public:
	Path();

	virtual void Draw(HDC hdc) override;

	void SetIndex(int index) { this->index = index; }
	void SetDebugVisit(bool debugVisit) { this->debugVisit = debugVisit; }
	void SetDebugToGo(bool debugToGo) { this->debugToGo = debugToGo; }

private:
	void DrawDebug(HDC hdc);

	int index;
	bool debugVisit;
	bool debugToGo;
};


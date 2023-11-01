#pragma once
#include "init.h"
#include <stack>
#include <list>

class CGameMap;

class AStar
{
	CGameMap* gameMap;

	std::stack<point> path;
	std::list<point> visitNode;

	bool bFound;

public:
	AStar(CGameMap* inGameMap) : gameMap(inGameMap)
	{
		bFound = false;
	}

	void ExtractMin(point& choicePos, int dx, int dy);
	bool FindPath(int sx, int sy, int dx, int dy);
	void Draw();
};


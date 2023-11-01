#pragma once
#include "init.h"
#include <stack>
#include <list>

class CGameMap;

class Dijkstra
{
	CGameMap* gameMap;

	std::stack<point> path;
	std::list<point> visitNode;

	bool bFound;

public:
	Dijkstra(CGameMap* inGameMap) : gameMap(inGameMap)
	{
		bFound = false;
	}

	void ExtractMin(point& choicePos);
	bool FindPath(int sx, int sy, int dx, int dy);
	void Draw();
};


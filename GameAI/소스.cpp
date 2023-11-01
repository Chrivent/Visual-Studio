#include "GameMap.h"
#include "Dijkstra.h"
#include "AStar.h"

int main()
{
	CGameMap* gameMap = new CGameMap(10, 10);
	AStar* shortestPath = new AStar(gameMap);

	shortestPath->Draw();
	shortestPath->FindPath(0, 9, 9, 0);
	shortestPath->Draw();

	if (gameMap)
		delete gameMap;

	if (shortestPath)
		delete shortestPath;

	return 0;
}
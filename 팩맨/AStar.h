#pragma once

#include "mecro.h"

class Path;
class PacMan;

class AStar
{
public:
	AStar(int** maps);
	~AStar();

	stack<Position> GetPathGridPositions() { return pathGridPositions; }
	bool GetDebug() { return debug; }

	bool FindPath(Position startGridPosition, Position endGridPosition, vector<Path*> paths, PacMan* pacMan);
	void ClearPath(vector<Path*> paths);

	void SetDebug(bool debug, vector<Path*> paths);

private:
	int** maps;
	int** weightMap;
	bool** visitMap;
	Position** parentGridPostions;
	vector<Position> visitNodes;

	bool foundPath;

	stack<Position> pathGridPositions;

	bool debug;

	void ExtractMin(Position& choiceGridPosition, Position endGridPosition, PacMan* pacMan);

	void SetWeight(Position position, int weight) { weightMap[position.y][position.x] = weight; }
	int GetWeight(Position position) { return weightMap[position.y][position.x]; }

	void SetVisit(Position position, bool visit) { visitMap[position.y][position.x] = visit; }
	bool GetVisit(Position position) { return visitMap[position.y][position.x]; }

	void ReleaseParent();
	void ResetWeightAndVisit();
	void ResetPathDebug(vector<Path*> paths);
};

#pragma once

#include "mecro.h"

class Path;
class Enemy;
class Pacman;

class AStar
{
public:
	AStar();
	~AStar();

	stack<Position> GetPathGridPositions() { return pathGridPositions; }
	bool GetDebug() const { return debug; }

	bool FindPath(Position startGridPosition, Position endGridPosition, Enemy* enemy, Pacman* pacman);
	void ClearPath(const vector<Path*>& paths);

	void SetDebug(bool debug, const vector<Path*>& paths);

private:
	int** weightMap;
	bool** visitMap;
	Position** parentGridPositions;
	vector<Position> visitNodes;

	bool foundPath;

	stack<Position> pathGridPositions;

	bool debug;

	void ExtractMin(Position& choiceGridPosition, Position endGridPosition, Enemy* enemy, Pacman* pacman) const;

	void SetWeight(Position position, int weight) const { weightMap[position.y][position.x] = weight; }
	int GetWeight(Position position) const { return weightMap[position.y][position.x]; }

	void SetVisit(Position position, bool visit) const { visitMap[position.y][position.x] = visit; }
	bool GetVisit(Position position) const { return visitMap[position.y][position.x]; }

	void ReleaseParent();
	void ResetWeightAndVisit() const;
	static void ResetPathDebug(const vector<Path*>& paths);
};

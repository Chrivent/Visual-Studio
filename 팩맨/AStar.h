#pragma once

#include "mecro.h"
#include "Path.h"

class AStar
{
public:
	AStar(int** map, int width, int height);
	~AStar();

	bool FindPath(Position startPos, Position endPos, vector<Path*> paths, int cellWidth, int cellHeight);
	void ClearPath(vector<Path*> paths);

	stack<Position> pathPoses;

	bool debug;

private:
	int** map;
	int width;
	int height;

	int** weightMap;
	bool** visitMap;
	Position** parentPoses;
	vector<Position> visitNodes;

	bool foundPath;

	void ExtractMin(Position& choicePos, Position endPos);

	void SetWeight(Position position, int weight) { weightMap[position.y][position.x] = weight; }
	int GetWeight(Position position) { return weightMap[position.y][position.x]; }

	void SetVisit(Position position, bool visit) { visitMap[position.y][position.x] = visit; }
	bool GetVisit(Position position) { return visitMap[position.y][position.x]; }

	void ReleaseParent();
	void ResetWeightAndVisit();

	bool CheckIsPath(Position position);
};

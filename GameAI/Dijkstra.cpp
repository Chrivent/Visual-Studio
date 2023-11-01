#include "Dijkstra.h"
#include "GameMap.h"
#include<iostream>

void Dijkstra::ExtractMin(point& choicePos)
{
	int min = INT_MAX;
	int width = gameMap->getWidth();
	int height = gameMap->getHeight();
	int curX, curY;

	std::list<point>::reverse_iterator curPos;

	for (curPos = visitNode.rbegin(); curPos != visitNode.rend(); curPos++)
	{
		for (int ty = -1; ty <= 1; ty++)
		{
			for (int tx = -1; tx <= 1; tx++)
			{
				curX = curPos->x + tx;
				curY = curPos->y + ty;

				if (curX < 0 || curX > width - 1 || curY < 0 || curY > height - 1)
					continue;
				if (tx == 0 && ty == 0)
					continue;

				if (gameMap->getMapVal(curX, curY) < min && gameMap->getVisitInfo(curX, curY) == false)
				{
					min = gameMap->getMapVal(curX, curY);
					choicePos = { curX, curY };
				}
			}
		}
	}
}

bool Dijkstra::FindPath(int sx, int sy, int dx, int dy)
{
	bFound = false;

	int width = gameMap->getWidth();
	int height = gameMap->getHeight();

	point** parent;
	parent = new point * [height];

	for (int i = 0; i < height; i++)
		parent[i] = new point[width];

	point choicePos;
	gameMap->setMapVal(sx, sy, 0);
	choicePos = { sx, sy };
	parent[sy][sx] = choicePos;

	for (int i = 0; i < width * height; i++)
	{
		gameMap->setVisitInfo(choicePos.x, choicePos.y, true);
		visitNode.push_back(choicePos);

		if (choicePos.x == dx && choicePos.y == dy)
		{
			bFound = true;
			break;
		}

		for (int ty = -1; ty <= 1; ty++)
		{
			for (int tx = -1; tx <= 1; tx++)
			{
				int nx = choicePos.x + tx;
				int ny = choicePos.y + ty;

				int dist;
				if (nx < 0 || nx > width - 1 || ny < 0 || ny > height - 1)
					continue;
				if (gameMap->getVisitInfo(nx, ny) == false)
				{
					dist = (tx == 0 || ty == 0) ? 10 : 14;

					int tcost = gameMap->getMapVal(choicePos.x, choicePos.y) + dist;
					if (gameMap->getMapVal(nx, ny) > tcost)
					{
						gameMap->setMapVal(nx, ny, tcost);
						parent[ny][nx] = choicePos;
					}
				}
			}
		}

		ExtractMin(choicePos);
	}

	if (bFound)
	{
		point p;
		p = { dx, dy };
		path.push(p);
		while (p.x != sx || p.y != sy)
		{
			p = parent[p.y][p.x];
			path.push(p);
		}

		return true;
	}

	return false;
}

void Dijkstra::Draw()
{
	gameMap->draw();
	if (bFound)
	{
		point p;
		do
		{
			p = path.top();
			std::cout << "(" << p.x << ", " << p.y << ") ==> ";
			path.pop();
		} while (!path.empty());

		std::cout << "최단 경로를 찾았습니다..." << std::endl;
	}
}

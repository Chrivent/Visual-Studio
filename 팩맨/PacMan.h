#pragma once

#include "mecro.h"
#include "Player.h"
#include "Wall.h"
#include "Coin.h"
#include "Enemy.h"
#include "Path.h"
#include "AStar.h"

#define WIDTH 19
#define HEIGHT 22

#define WALL 1
#define COIN 2
#define PLAYER 5
#define ENEMY 6

struct EnemyInformation
{
    Position enemyTargetPosition;
    bool enemyFindPath;
    int enemyX;
    int enemyY;
};

class PacMan : public wMecro::Game
{
public:
	PacMan(int Width, int Height);
	~PacMan();

	void PlayerGaspUpdate();
	void PlayerMoveUpdate();
    void EnemyMoveUpdate();

    void SetPlayerDirection(Direction direction);

	int playerSpeed;
    int enemySpeed;

protected:
	virtual void Draw(HDC hdc, HWND hWnd) override;

private:
    void CheckCoin();

	int cellWidth;
	int cellHeight;

    bool debug;

	Player* player;
    vector<Wall*> walls;
    vector<Coin*> coins;
    vector<Enemy*> enemys;
    vector<Path*> paths;

    Direction playerDirection;
    int playerX;
    int playerY;
    int playerTargetX;
    int playerTargetY;

    int enemyCount;
    vector<Position> enemyTargetPositions;
    vector<int> enemyEndXs;
    vector<int> enemyEndYs;
    vector<bool> enemyFindPaths;
    vector<int> enemyXs;
    vector<int> enemyYs;
    vector<AStar*> enemyAStars;

    int** map;
    int mapData[HEIGHT][WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
        {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
        {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
        {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
        {1,1,1,1,2,1,1,1,0,1,0,1,1,1,2,1,1,1,1},
        {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
        {1,1,1,1,2,1,0,1,1,4,1,1,0,1,2,1,1,1,1},
        {0,0,0,0,2,0,0,1,0,6,0,1,0,0,2,0,0,0,0},
        {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
        {0,0,0,1,2,1,0,0,0,0,0,0,0,1,2,1,0,0,0},
        {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
        {1,3,2,1,2,2,2,2,2,0,2,2,2,2,2,1,2,3,1},
        {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
        {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
        {1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1},
        {1,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
};


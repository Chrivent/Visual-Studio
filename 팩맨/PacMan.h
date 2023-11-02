#pragma once

#include "mecro.h"
#include "Player.h"
#include "Wall.h"
#include "Coin.h"
#include "Enemy.h"
#include "Path.h"

#define WIDTH 19
#define HEIGHT 22

#define WALL 1
#define COIN 2
#define DOOR 4
#define PLAYER 5
#define ENEMY 6
#define TRANSPARENT_WALL 7

class PacMan : public wMecro::Game
{
public:
	PacMan(Scale clientScale);
	~PacMan();

    void SetPlayerSpeed(int playerSpeed) { this->playerSpeed = playerSpeed; }
    void SetEnemySpeed(int enemySpeed) { this->enemySpeed = enemySpeed; }
    void SetDebug(bool debug) { this->debug = debug; }

    int** GetMaps() { return maps; }
    Scale GetCellScale() { return cellScale; }
    Player* GetPlayer() { return player; }
    vector<vector<Path*>> GetPaths() { return paths; }
    int GetEnemySpeed() { return enemySpeed; }
    int GetDoorOpenCount() { return doorOpenCount; }
    bool GetDebug() { return debug; }

	void PlayerMoveUpdate();
	void PlayerGaspUpdate();
    void EnemyMoveUpdate();
    void EnemyStepUpdate();

    void SetPlayerDirection(Direction direction);
    void OpenDoor();
    bool GridPositionIsPath(Position position);

    Position ConvertPositionToGridPosition(Position position);
    Position ConvertGridPositionToPosition(Position gridPosition);

protected:
	virtual void Draw(HDC hdc, HWND hWnd) override;

private:
    void CheckCoin();
    bool CheckPlayerPath(int map);

	Player* player;
    vector<Wall*> walls;
    vector<Coin*> coins;
    vector<Enemy*> enemys;
    vector<vector<Path*>> paths;
    vector<Position> doorPositions;

    Scale cellScale;
    Direction playerDirection;

    int playerSpeed;
    int enemySpeed;
    int doorOpenCount;

    bool debug;

    int** maps;
    int mapData[HEIGHT][WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
        {1,3,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,3,1},
        {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
        {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
        {1,1,1,1,2,1,1,1,0,1,0,1,1,1,2,1,1,1,1},
        {7,7,7,1,2,1,0,0,0,0,0,0,0,1,2,1,7,7,7},
        {1,1,1,1,2,1,0,1,1,4,1,1,0,1,2,1,1,1,1},
        {0,0,0,0,2,0,0,1,0,6,0,1,0,0,2,0,0,0,0},
        {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
        {7,7,7,1,2,1,0,0,0,0,0,0,0,1,2,1,7,7,7},
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


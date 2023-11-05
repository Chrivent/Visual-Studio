#pragma once

#include "mecro.h"
#include "Player.h"
#include "Wall.h"
#include "Coin.h"
#include "Enemy.h"
#include "Path.h"
#include "Door.h"

#define WIDTH 19
#define HEIGHT 22

#define WALL 1
#define COIN 2
#define BIG_COIN 3
#define DOOR 4
#define PLAYER 5
#define ENEMY 6
#define TRANSPARENT_WALL 7

class Pacman : public wMecro::Game
{
public:
	Pacman(Scale clientScale);
	~Pacman() override;

    void SetDebug(bool debug) { this->debug = debug; }
    void SetEnemyHunted(bool hunted) { this->enemyHunted = hunted; }

    Player* GetPlayer() const { return player; }
    vector<Coin*>& GetCoins() { return coins; }
    vector<Enemy*> GetEnemies() { return enemies; }
    vector<vector<Path*>> GetPaths() { return paths; }
    int** GetMaps() const { return maps; }
    wMecro::Transform GetScoreTextTransform() const { return scoreTextTransform; }
    Scale GetCellScale() const { return cellScale; }
    Direction GetInputDirection() const { return inputDirection; }
    int GetDoorOpenCount() const { return doorOpenCount; }
    bool GetEnemyHunted() const { return enemyHunted; }
    bool GetGameOver() const { return gameOver; }
    bool GetDebug() const { return debug; }

    void InitParameter();
    void InitEntity();
    void DeleteEntity();

	void PlayerMoveUpdate();
	void PlayerGaspUpdate() const;
    void EnemyMoveUpdate();
    void EnemyStepUpdate() const;

    void SetInputDirection(Direction direction);
    void AddScore(int score);
    void ResetAllHuntedTimer() const;
    void GameOver();
    void ResetGame();
    void GameClear();
    bool AllEnemyIsHunted() const;

    Position ConvertPositionToGridPosition(Position position, int speed) const;
    Position ConvertGridPositionToPosition(Position gridPosition) const;

protected:
	void Draw(HDC hdc, HWND hWnd) override;

private:
	Player* player;
    vector<Wall*> walls;
    vector<Coin*> coins;
    vector<Enemy*> enemies;
    vector<vector<Path*>> paths;
    vector<Door*> doors;
    wMecro::Transform scoreTextTransform;
    wMecro::Transform gameClearTextTransform;

    Scale cellScale;
    Direction inputDirection;
    int doorOpenCount;
    int doorOpenTime;
    int doorOpenTimer;
    bool enemyHunted;
    int score;
    bool gameOver;
    bool gameClear;

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
        {7,7,7,1,2,1,0,0,0,6,0,0,0,1,2,1,7,7,7},
        {1,1,1,1,2,1,0,1,1,4,1,1,0,1,2,1,1,1,1},
        {0,0,0,0,2,0,0,1,6,6,6,1,0,0,2,0,0,0,0},
        {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
        {7,7,7,1,2,1,0,0,0,0,0,0,0,1,2,1,7,7,7},
        {1,1,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
        {1,3,2,1,2,2,2,2,2,5,2,2,2,2,2,1,2,3,1},
        {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
        {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
        {1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
};


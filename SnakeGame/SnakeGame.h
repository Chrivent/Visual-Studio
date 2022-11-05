#pragma once

#include "LinkedList.h"
#include "Food.h"

enum SCENE
{
	SCENE_MAINMENU,
	SCENE_PLAY,
	SCENE_LEVEL,
	SCENE_EXIT
};

enum MAINMENU
{
	MAINMENU_PLAY,
	MAINMENU_LEVEL,
	MAINMENU_EXIT
};

enum LEVELMENU
{
	LEVELMENU_EASY,
	LEVELMENU_NORMAL,
	LEVELMENU_HARD
};

enum PLAYSIZE
{
	PLAYSIZE_EASY = 20,
	PLAYSIZE_NORMAL = 30,
	PLAYSIZE_HARD = 40
};

enum MOVECLOCK
{
	MOVECLOCK_EASY = 300,
	MOVECLOCK_NORMAL = 200,
	MOVECLOCK_HARD = 100
};

class SnakeGame : public Game
{
private:
	LinkedList bodys;
	Clock moveClock;
	Food food;
	Position lastPos;

	int mainSize;
	int mainSelect;
	int levelSelect;
	int playSize;
	bool init;
	int direction;

	void DrawMainMenu();
	void DrawLevelMenu();
	void SetLevel();
	void SetFoodPositionRand();
	void Init();
	bool CheckCanMove(int hit);
	void Move(int index, Position position);
	bool CheckGameOver(Position headPos);
	void GameOver();
	void MainMenuScene();
	void PlayScene();
	void LevelScene();
	void Draw();
	void Start();
	bool Update();

public:
	SnakeGame();
};
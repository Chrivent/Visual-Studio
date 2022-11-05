#include "SnakeGame.h"

void SnakeGame::DrawMainMenu()
{
	DrawBox(0, 0, mainSize, mainSize, C_PUPPLE);
	DrawTextMiddle(mainSize / 2, mainSize / 4, "[ Snake Game ]", C_PLUM);
	DrawTextMiddle(mainSize / 2, mainSize / 2, "Start", mainSelect == MAINMENU_PLAY ? C_GREEN : C_GRAY);
	DrawTextMiddle(mainSize / 2, mainSize / 5 * 3, "Level", mainSelect == MAINMENU_LEVEL ? C_GREEN : C_GRAY);
	DrawTextMiddle(mainSize / 2, mainSize / 10 * 7, "Exit", mainSelect == MAINMENU_EXIT ? C_GREEN : C_GRAY);
}

void SnakeGame::DrawLevelMenu()
{
	DrawBox(0, 0, mainSize, mainSize, C_PUPPLE);
	DrawTextMiddle(mainSize / 2, mainSize / 4, "Easy", levelSelect == LEVELMENU_EASY ? C_GREEN : C_GRAY);
	DrawTextMiddle(mainSize / 2, mainSize / 2, "Normal", levelSelect == LEVELMENU_NORMAL ? C_GREEN : C_GRAY);
	DrawTextMiddle(mainSize / 2, mainSize / 4 * 3, "Hard", levelSelect == LEVELMENU_HARD ? C_GREEN : C_GRAY);
}

void SnakeGame::SetLevel()
{
	switch (levelSelect)
	{
	case LEVELMENU_EASY:
		moveClock.SetTime(MOVECLOCK_EASY);

		playSize = PLAYSIZE_EASY;
		break;

	case LEVELMENU_NORMAL:
		moveClock.SetTime(MOVECLOCK_NORMAL);

		playSize = PLAYSIZE_NORMAL;
		break;

	case LEVELMENU_HARD:
		moveClock.SetTime(MOVECLOCK_HARD);

		playSize = PLAYSIZE_HARD;
		break;
	}
}

void SnakeGame::SetFoodPositionRand()
{
	bool check = true;

	while (check)
	{
		check = false;

		food.position = { RandNum(1, playSize - 1), RandNum(1, playSize - 1) };

		for (int i = 0; i < bodys.GetLength(); i++)
		{
			if (bodys.GetNode(i)->position == food.position)
				check = true;
		}
	}
}

void SnakeGame::Init()
{
	SetScreenSize(playSize, playSize);

	int center = playSize / 2;

	bodys.Insert(0, { center, center });
	bodys.GetNode(0)->ActivateHead();

	direction = NULL;

	SetFoodPositionRand();
	Draw();

	init = true;
}

bool SnakeGame::CheckCanMove(int hit)
{
	Node* firstBody = bodys.GetNode(0);
	Node* secondBody = bodys.GetNode(1);

	if (secondBody != nullptr)
	{
		Position secondPos = secondBody->position;

		Position leftPos = firstBody->position;
		Position rightPos = firstBody->position;
		Position upPos = firstBody->position;
		Position downPos = firstBody->position;

		leftPos.x--;
		rightPos.x++;
		upPos.y--;
		downPos.y++;

		if (hit == LEFT && secondPos != leftPos)
			return true;
		else if (hit == RIGHT && secondPos != rightPos)
			return true;
		else if (hit == UP && secondPos != upPos)
			return true;
		else if (hit == DOWN && secondPos != downPos)
			return true;
		else
			return false;
	}

	return true;
}

void SnakeGame::Move(int index, Position position)
{
	Position pos = bodys.GetNode(index)->position;

	bodys.GetNode(index)->position = position;

	index++;

	if (index < bodys.GetLength())
		Move(index, pos);
	else
		lastPos = pos;

	return;
}

bool SnakeGame::CheckGameOver(Position headPos)
{
	for (int i = 1; i < bodys.GetLength(); i++)
	{
		if (bodys.GetNode(i)->position == headPos)
			return true;
	}

	if (headPos.x == 0 || headPos.x == playSize - 1)
		return true;

	if (headPos.y == 0 || headPos.y == playSize - 1)
		return true;

	return false;
}

void SnakeGame::GameOver()
{
	bodys.RemoveAll();

	scene = SCENE_MAINMENU;

	SetScreenSize(mainSize, mainSize);
	Draw();

	init = false;
}

void SnakeGame::MainMenuScene()
{
	switch (Hit())
	{
	case UP:
		if (mainSelect > MAINMENU_PLAY)
		{
			mainSelect--;

			Draw();
		}
		break;

	case DOWN:
		if (mainSelect < MAINMENU_EXIT)
		{
			mainSelect++;

			Draw();
		}
		break;

	case ENTER:
		scene = mainSelect + 1;

		if (scene == SCENE_LEVEL)
			Draw();
		break;
	}
}

void SnakeGame::PlayScene()
{
	if (init == false)
		Init();
	else
	{
		if (moveClock.Alarm())
		{
			Position headPos = bodys.GetNode(0)->position;

			switch (direction)
			{
			case LEFT:
				headPos.x--;
				break;

			case RIGHT:
				headPos.x++;
				break;

			case UP:
				headPos.y--;
				break;

			case DOWN:
				headPos.y++;
			}

			Move(0, headPos);

			if (headPos == food.position)
			{
				bodys.Append(lastPos);

				SetFoodPositionRand();
			}
			else if (CheckGameOver(headPos))
			{
				GameOver();

				return;
			}

			Draw();
		}
	}

	int hit = Hit();

	if ((hit == LEFT || hit == RIGHT || hit == UP || hit == DOWN) && CheckCanMove(hit))
		direction = hit;
	else if (hit == ESC)
	{
		GameOver();

		return;
	}
}

void SnakeGame::LevelScene()
{
	int tmp = levelSelect;

	switch (Hit())
	{
	case UP:
		if (levelSelect > LEVELMENU_EASY)
		{
			levelSelect--;

			Draw();
		}
		break;

	case DOWN:
		if (levelSelect < LEVELMENU_HARD)
		{
			levelSelect++;

			Draw();
		}
		break;

	case ENTER:
		SetLevel();

		scene = SCENE_MAINMENU;

		Draw();
		break;

	case ESC:
		switch (playSize)
		{
		case PLAYSIZE_EASY:
			levelSelect = LEVELMENU_EASY;
			break;

		case PLAYSIZE_NORMAL:
			levelSelect = LEVELMENU_NORMAL;
			break;

		case PLAYSIZE_HARD:
			levelSelect = LEVELMENU_HARD;
			break;
		}

		scene = SCENE_MAINMENU;

		Draw();
		break;
	}
}

void SnakeGame::Draw()
{
	system("cls");

	switch (scene)
	{
	case SCENE_MAINMENU:
		DrawMainMenu();
		break;

	case SCENE_PLAY:
		for (int i = 0; i < bodys.GetLength(); i++)
			bodys.GetNode(i)->Draw();

		DrawEmptyRectangle(0, 0, playSize, playSize, "¢Ì");

		food.Draw();
		break;

	case SCENE_LEVEL:
		DrawLevelMenu();
		break;
	}
}

void SnakeGame::Start()
{
	mainSelect = MAINMENU_PLAY;
	levelSelect = LEVELMENU_NORMAL;

	SetLevel();
	SetScreenSize(mainSize, mainSize);
	Draw();
}

bool SnakeGame::Update()
{
	switch (scene)
	{
	case SCENE_MAINMENU:
		MainMenuScene();
		break;

	case SCENE_PLAY:
		PlayScene();
		break;

	case SCENE_LEVEL:
		LevelScene();
		break;

	case SCENE_EXIT:
		return false;
	}

	return true;
}

SnakeGame::SnakeGame()
{
	mainSize = 20;
	mainSelect = MAINMENU_PLAY;
	levelSelect = LEVELMENU_NORMAL;
	playSize = PLAYSIZE_NORMAL;
	init = false;
	direction = NULL;
}
#include "Eaten.h"
#include "Enemy.h"
#include "Pacman.h"
#include "InBox.h"

Eaten& Eaten::Instance()
{
	static Eaten instance;

	return instance;
}

void Eaten::Start(Enemy* enemy, Pacman* pacman)
{
	const float speedRate = enemy->GetEatenSpeedRate();

	enemy->ChangeSpeed(speedRate);
}

void Eaten::Update(Enemy* enemy, Pacman* pacman)
{
	if (!enemy->GetEaten())
		enemy->ChangeState(&InBox::Instance(), pacman);
	else
		enemy->MoveEaten(pacman);
}

void Eaten::Exit(Enemy* enemy, Pacman* pacman)
{
	const vector<Path*> paths = pacman->GetPaths()[enemy->GetIndex()];
	AStar* aStar = enemy->GetAStar();

	aStar->ClearPath(paths);
	enemy->ResetSpeed();
}

#include "Hunter.h"
#include "Enemy.h"
#include "Pacman.h"
#include "Hunted.h"

Hunter& Hunter::Instance()
{
	static Hunter instance;

	return instance;
}

void Hunter::Start(Enemy* enemy, Pacman* pacman)
{
	enemy->SetHunter(true);
}

void Hunter::Update(Enemy* enemy, Pacman* pacman)
{
	if (pacman->GetEnemyHunted())
		enemy->ChangeState(&Hunted::Instance(), pacman);
	else if (enemy->GetHunted())
		enemy->ChangeState(&Hunted::Instance(), pacman);
	else
		enemy->MoveHunter(pacman);
}

void Hunter::Exit(Enemy* enemy, Pacman* pacman)
{
	const vector<Path*> paths = pacman->GetPaths()[enemy->GetIndex()];
	AStar* aStar = enemy->GetAStar();

	enemy->SetHunter(false);
	aStar->ClearPath(paths);
}

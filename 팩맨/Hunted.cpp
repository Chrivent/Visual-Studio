#include "Hunted.h"
#include "Enemy.h"
#include "Pacman.h"
#include "Hunter.h"
#include "Eaten.h"

Hunted& Hunted::Instance()
{
	static Hunted instance;

	return instance;
}

void Hunted::Start(Enemy* enemy, Pacman* pacman)
{
	enemy->SetHunted(true);
	enemy->ChangeSpeed(enemy->GetHuntedSpeedRate());
}

void Hunted::Update(Enemy* enemy, Pacman* pacman)
{
	if (!enemy->GetHunted())
		enemy->ChangeState(&Hunter::Instance(), pacman);
	else if (enemy->GetEaten())
		enemy->ChangeState(&Eaten::Instance(), pacman);
	else
		enemy->MoveHunted(pacman);
}

void Hunted::Exit(Enemy* enemy, Pacman* pacman)
{
	enemy->SetHunted(false);
	enemy->ResetHuntedTimer();
	enemy->ResetSpeed();
}

#include "InBox.h"
#include "Enemy.h"
#include "Pacman.h"
#include "Hunter.h"

InBox& InBox::Instance()
{
    static InBox instance;

    return instance;
}

void InBox::Start(Enemy* enemy, Pacman* pacman)
{

}

void InBox::Update(Enemy* enemy, Pacman* pacman)
{
    if (pacman->GetDoorOpenCount() >= enemy->GetIndex())
        enemy->ChangeState(&Hunter::Instance(), pacman);
    else
        enemy->MoveInBox(pacman);
}

void InBox::Exit(Enemy* enemy, Pacman* pacman)
{

}

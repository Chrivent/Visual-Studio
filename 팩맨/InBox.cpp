#include "InBox.h"
#include "Enemy.h"
#include "PacMan.h"
#include "Hunter.h"

InBox& InBox::Instance()
{
    static InBox instance;

    return instance;
}

void InBox::Update(Enemy* enemy, PacMan* pacMan)
{
    if (pacMan->GetDoorOpenCount() > enemy->GetIndex())
        enemy->SetState(&Hunter::Instance());
    else
        enemy->MoveStay(pacMan->GetEnemySpeed());
}

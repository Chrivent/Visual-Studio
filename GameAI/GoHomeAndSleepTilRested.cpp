#include "GoHomeAndSleepTilRested.h"

#include<iostream>
#include<Windows.h>

#include "Miner.h"
#include "EnterMineAndDigForNugget.h"

GoHomeAndSleepTilRested& GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* miner)
{
	Sleep(1000);
	miner->Rest();
	miner->ChangeState(&EnterMineAndDigForNugget::Instance());
	std::cout << "[통장 : " << miner->GetBankGold() << ", 금액 : " << miner->GetGold() << ", 목마름 : " << miner->GetThirst() << "] 휴식을 취합니다. " << std::endl;
}

void GoHomeAndSleepTilRested::Execute(Miner* miner)
{
}

void GoHomeAndSleepTilRested::Exit(Miner* miner)
{
}

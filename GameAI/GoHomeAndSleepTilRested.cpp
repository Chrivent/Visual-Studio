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
	std::cout << "[���� : " << miner->GetBankGold() << ", �ݾ� : " << miner->GetGold() << ", �񸶸� : " << miner->GetThirst() << "] �޽��� ���մϴ�. " << std::endl;
}

void GoHomeAndSleepTilRested::Execute(Miner* miner)
{
}

void GoHomeAndSleepTilRested::Exit(Miner* miner)
{
}

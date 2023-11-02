#include "EnterMineAndDigForNugget.h"

#include<iostream>
#include<Windows.h>

#include "Miner.h"
#include "VisitBankAndDepositGold.h"
#include "QuenchThirst.h"

EnterMineAndDigForNugget& EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;

	return instance;
}

void EnterMineAndDigForNugget::Enter(Miner* miner)
{
}

void EnterMineAndDigForNugget::Execute(Miner* miner)
{
	Sleep(1000);
	miner->Earn();
	if (miner->GetGold() >= miner->GetStandardGold())
		miner->ChangeState(&VisitBankAndDepositGold::Instance());
	else if (miner->GetThirst() >= miner->GetStandardThirst())
		miner->ChangeState(&QuenchThirst::Instance());
	std::cout << "[통장 : " << miner->GetBankGold() << ", 금액 : " << miner->GetGold() << ", 목마름 : " << miner->GetThirst() << "] 광질하러 갑니다. " << std::endl;
}

void EnterMineAndDigForNugget::Exit(Miner* miner)
{
}

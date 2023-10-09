#include "VisitBankAndDepositGold.h"

#include<iostream>
#include<Windows.h>

#include "Miner.h"
#include "VisitBankAndDepositGold.h"
#include "GoHomeAndSleepTilRested.h"
#include "EnterMineAndDigForNugget.h"

VisitBankAndDepositGold& VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return instance;
}

void VisitBankAndDepositGold::Enter(Miner* miner)
{
}

void VisitBankAndDepositGold::Execute(Miner* miner)
{
	Sleep(1000);
	miner->Deposit();
	if (miner->GetBankGold() > miner->GetStandardRich())
		miner->ChangeState(&GoHomeAndSleepTilRested::Instance());
	else
		miner->ChangeState(&EnterMineAndDigForNugget::Instance());
	std::cout << "[통장 : " << miner->GetBankGold() << ", 금액 : " << miner->GetGold() << ", 목마름 : " << miner->GetThirst() << "] 입금하러 갑니다. " << std::endl;
}

void VisitBankAndDepositGold::Exit(Miner* miner)
{
}

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
	std::cout << "[���� : " << miner->GetBankGold() << ", �ݾ� : " << miner->GetGold() << ", �񸶸� : " << miner->GetThirst() << "] �Ա��Ϸ� ���ϴ�. " << std::endl;
}

void VisitBankAndDepositGold::Exit(Miner* miner)
{
}

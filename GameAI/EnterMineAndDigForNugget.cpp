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
	std::cout << "[���� : " << miner->GetBankGold() << ", �ݾ� : " << miner->GetGold() << ", �񸶸� : " << miner->GetThirst() << "] �����Ϸ� ���ϴ�. " << std::endl;
}

void EnterMineAndDigForNugget::Exit(Miner* miner)
{
}

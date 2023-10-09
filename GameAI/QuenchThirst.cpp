#include "QuenchThirst.h"

#include<iostream>
#include<Windows.h>

#include "Miner.h"
#include "EnterMineAndDigForNugget.h"

QuenchThirst& QuenchThirst::Instance()
{
	static QuenchThirst instance;

	return instance;
}

void QuenchThirst::Enter(Miner* miner)
{
}

void QuenchThirst::Execute(Miner* miner)
{
	Sleep(1000);
	miner->Drink();
	if (miner->GetThirst() < miner->GetStandardThirst())
		miner->ChangeState(&EnterMineAndDigForNugget::Instance());
	std::cout << "[통장 : " << miner->GetBankGold() << ", 금액 : " << miner->GetGold() << ", 목마름 : " << miner->GetThirst() << "] 물을 마십니다. " << std::endl;
}

void QuenchThirst::Exit(Miner* miner)
{
}

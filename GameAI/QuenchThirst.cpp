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
	std::cout << "[���� : " << miner->GetBankGold() << ", �ݾ� : " << miner->GetGold() << ", �񸶸� : " << miner->GetThirst() << "] ���� ���ʴϴ�. " << std::endl;
}

void QuenchThirst::Exit(Miner* miner)
{
}

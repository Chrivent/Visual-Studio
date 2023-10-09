#include "Miner.h"

void Miner::Update()
{
	thirst++;
	currentState->Execute(this);
}

void Miner::ChangeState(State* newState)
{
	currentState->Exit(this);
	currentState = newState;
	currentState->Enter(this);
}

void Miner::Drink()
{
	thirst = 0;
}

void Miner::Earn()
{
	gold++;
}

void Miner::Deposit()
{
	bankGold += gold;
	gold = 0;
}

void Miner::Rest()
{
	bankGold = 0;
}

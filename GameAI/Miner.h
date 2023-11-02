#pragma once

#include "BaseGameEntity.h"
#include "State.h"

class Miner : public BaseGameEntity
{
private:
	State* currentState;
	int thirst;
	int gold;
	int standardThirst;
	int standardGold;
	int bankGold;
	int standardRich;

public:
	Miner(std::string initName, State* initState, int initStandardThirst, int initStandardGold, int initStandardRich) :
		BaseGameEntity(initName),
		currentState(initState),
		thirst(0),
		gold(0),
		standardThirst(initStandardThirst),
		standardGold(initStandardGold),
		bankGold(0),
		standardRich(initStandardRich)
	{}

	int GetThirst() { return thirst; }
	int GetGold() { return gold; }
	int GetStandardThirst() { return standardThirst; }
	int GetStandardGold() { return standardGold; }
	int GetBankGold() { return bankGold; }
	int GetStandardRich() { return standardGold; }

	virtual void Update() override;

	void ChangeState(State* newState);
	void Drink();
	void Earn();
	void Deposit();
	void Rest();
};


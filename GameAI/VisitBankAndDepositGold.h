#pragma once

#include "State.h"

class VisitBankAndDepositGold : public State
{
public:
	static VisitBankAndDepositGold& Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
};


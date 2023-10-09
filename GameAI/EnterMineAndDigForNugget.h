#pragma once

#include "State.h"

class EnterMineAndDigForNugget : public State
{
public:
	static EnterMineAndDigForNugget& Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
};


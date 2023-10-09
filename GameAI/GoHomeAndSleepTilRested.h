#pragma once

#include "State.h"

class GoHomeAndSleepTilRested : public State
{
public:
	static GoHomeAndSleepTilRested& Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
};


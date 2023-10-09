#pragma once

#include "State.h"

class QuenchThirst : public State
{
public:
	static QuenchThirst& Instance();

	virtual void Enter(Miner* miner) override;
	virtual void Execute(Miner* miner) override;
	virtual void Exit(Miner* miner) override;
};


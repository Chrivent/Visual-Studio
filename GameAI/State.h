#pragma once

class Miner;

class State
{
public:
	virtual void Enter(Miner* miner) = 0;
	virtual void Execute(Miner* miner) = 0;
	virtual void Exit(Miner* miner) = 0;
};


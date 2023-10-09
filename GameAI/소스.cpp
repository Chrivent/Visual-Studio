#include "Miner.h"
#include "EnterMineAndDigForNugget.h"

int main()
{
	Miner miner("Miner", new EnterMineAndDigForNugget, 5, 7, 15);

	while(true)
		miner.Update();

	return 0;
}
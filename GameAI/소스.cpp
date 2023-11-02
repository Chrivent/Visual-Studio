#include "Miner.h"
#include "EnterMineAndDigForNugget.h"

int main()
{
	Miner miner("Miner", &EnterMineAndDigForNugget::Instance(), 5, 7, 15);

	while(true)
		miner.Update();

	return 0;
}
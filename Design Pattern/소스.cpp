#include <iostream>

#include "Americano.h"
#include "CafeLatte.h"

int main()
{
	Coffee* coffee[2];

	coffee[0] = new Americano;
	coffee[1] = new CafeLatte;

	for (int i = 0; i < 2; i++)
		coffee[i]->PutExtra();

	for (int i = 0; i < 2; i++)
	{
		if (coffee[i] != nullptr)
			delete coffee[i];
	}

	return 0;
}
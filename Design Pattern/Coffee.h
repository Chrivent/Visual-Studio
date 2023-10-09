#pragma once

#include<iostream>
#include<string>

class Coffee
{
protected:
	std::string name;

public:
	void MakeCoffee();
	void PutEspresso();
	void TakeOut();

	virtual void PutExtra() = 0;
};


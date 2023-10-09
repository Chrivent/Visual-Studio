#pragma once

#include<string>

class BaseGameEntity
{
private:
	std::string name;

public:
	BaseGameEntity(std::string initName) : name(initName) {}

	virtual void Update() = 0;

	std::string GetName() { return name; }
};


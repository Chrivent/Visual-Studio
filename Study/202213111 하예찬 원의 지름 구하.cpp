#include<iostream>

using namespace std;

class Circle
{
private:
	int radius;

public:
	Circle(int radius)
	{
		this->radius = radius;
	}

	int GetDiameter()
	{
		return radius * 2;
	}
};

int main()
{
	int radius;

	cin >> radius;

	Circle circle(radius);

	cout << circle.GetDiameter();

	return 0;
}
#include<iostream>
#include<math.h>
#include<vector>

using namespace std;

class Position
{
public:
	int x;
	int y;
};

float Pi()
{
	return (float)atan(1) * 4;
}

float DiagonalLength(Position position1, Position position2)
{
	int width = position1.x - position2.x;
	int height = position1.y - position2.y;

	return (float)sqrt(pow(width, 2) + pow(height, 2));
}

Position AnglePosition(Position position, int length, int angle)
{
	return { int(position.x + length * cos(angle * Pi() / 180)), int(position.y + length * sin(angle * Pi() / 180)) };
}

class Circle
{
private:
	Position position;
	int radius;

public:
	Circle(int x, int y, int radius)
	{
		this->position.x = x;
		this->position.y = y;
		this->radius = radius;
	}

	Position GetPosition()
	{
		return position;
	}

	int GetRadius()
	{
		return radius;
	}

	bool CheckIn(Position position)
	{
		if (DiagonalLength(this->position, position) <= radius)
			return true;

		return false;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int circleCount;
	int nodabCount = 0;

	vector<Circle*> circle;

	cin >> circleCount;

	for (int i = 0; i < circleCount; i++)
	{
		int x, y, r;

		cin >> x >> y >> r;

		circle.push_back(new Circle(x, y, r));
	}

	for (int i = 0; i < circleCount; i++)
	{
		bool nodabCicle = true;

		for (int angle = 0; angle < 360; angle++)
		{
			Position pos = AnglePosition(circle[i]->GetPosition(), circle[i]->GetRadius(), angle);

			bool inOtherCircle = false;

			for (int j = 0; j < circleCount; j++)
			{
				if (i != j)
				{
					if (circle[j]->CheckIn(pos))
						inOtherCircle = true;
				}
			}

			if (inOtherCircle == false)
				nodabCicle = false;
		}

		if (nodabCicle == true)
			nodabCount++;
	}

	cout << nodabCount;

	for (int i = 0; i < circleCount; i++)
	{
		delete circle[i];

		circle[i] = nullptr;
	}

	return 0;
}
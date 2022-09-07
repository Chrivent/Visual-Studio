#include<iostream>
#include<vector>

using namespace std;

int PowDiagonalLength(int x1, int y1, int x2, int y2)
{
	int width = x1 - x2;
	int height = y1 - y2;

	return width * width + height * height;
}

class Circle
{
public:
	int x;
	int y;
	int radius;

	Circle(int x, int y, int radius)
	{
		this->x = x;
		this->y = y;
		this->radius = radius;
	}

	bool CheckIn(int x, int y)
	{
		if (PowDiagonalLength(this->x, this->y, x, y) <= radius * radius)
			return true;

		return false;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int circleCount;
	int nodabCount = 0;

	vector<Circle*> circle;

	scanf("%d", &circleCount);

	for (int i = 0; i < circleCount; i++)
	{
		int x, y, r;

		scanf("%d %d %d", &x, &y, &r);

		circle.push_back(new Circle(x, y, r));
	}

	for (int i = 0; i < circleCount; i++)
	{
		int thisX = circle[i]->x;
		int thisY = circle[i]->y;
		int thisR = circle[i]->radius;

		bool nodabCicle = true;

		for (int x = thisX - thisR; x <= thisX + thisR; x++)
		{
			for (int y = thisY - thisR; y <= thisY + thisR; y++)
			{
				if (circle[i]->CheckIn(x, y))
				{
					bool inOtherCircle = false;

					for (int j = 0; j < circleCount; j++)
					{
						if (i != j)
						{
							if (circle[j]->CheckIn(x, y))
								inOtherCircle = true;
						}
					}

					if (inOtherCircle == false)
						nodabCicle = false;
				}
			}
		}

		if (nodabCicle == true)
			nodabCount++;
	}

	printf("%d", nodabCount);

	for (int i = 0; i < circleCount; i++)
	{
		delete circle[i];

		circle[i] = nullptr;
	}

	return 0;
}
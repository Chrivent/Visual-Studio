#include<iostream>

using namespace std;

class Box
{
private:
	int width;
	int length;
	int height;

public:
	void SetScale(int width, int length, int height)
	{
		this->width = width;
		this->length = length;
		this->height = height;
	}

	int CalVolume()
	{
		return width * length * height;
	}
};

int main()
{
	Box box;

	box.SetScale(2, 3, 4);

	cout << "ºÎÇÇ : " << box.CalVolume();

	return 0;
}
#include<iostream>
#include<string>

using namespace std;

int GetSize(int page)
{
	int size = 0;

	int tmp = page;

	while (tmp)
	{
		tmp /= 10;

		size++;
	}

	return size;
}

void Test1()
{
	int page;
	int numCount[10] = { 0 };

	cin >> page;

	for (int i = page; i > 0; i--)
	{
		int tmp = i;

		int zeroCount = 0;

		string str = to_string(tmp);

		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == '0')
				zeroCount++;
		}

		numCount[0] += zeroCount;

		for (int j = 1000000000; j > 0; j /= 10)
		{
			if (tmp >= j)
			{
				int num = tmp / j;

				for (int k = 0; k < 10; k++)
				{
					if (k == num)
					{
						numCount[k]++;

						break;
					}
				}

				tmp = tmp % j;
			}
		}
	}

	for (int i = 0; i < 10; i++)
		cout << numCount[i] << " ";
}

void Test2()
{
	int page;
	int numCount[10] = { 0 };

	cin >> page;

	string str = to_string(page);

	for (int num = 0; num < 10; num++)
	{
		for (int j = 0; j < str.size(); j++)
		{
			int tmpSize = 1;

			for (int k = 0; k < j; k++)
				tmpSize *= 10;

			int tmp = page / tmpSize / 10 * 10 + ((num > str[j] - '0') ? (page % tmpSize + 1) : 0);

			numCount[num] += tmp;
		}
	}

	for (int i = 0; i < 10; i++)
		cout << numCount[i] << " ";
}

void Test3()
{
	int page;
	int numCount[10] = { 0 };

	cin >> page;

	int maxSize = GetSize(page);

	for (int num = 0; num < 10; num++)
	{
		switch (num)
		{
		case 0:
			for (int size = 0; size < maxSize; size++)
			{
				int tmp = 10;

				for (int i = 0; i < size; i++)
					tmp *= 10;

				numCount[num] += page / tmp * tmp / 10;
			}
			break;

		case 1:
			for (int size = 0; size < maxSize; size++)
			{
				int tmp = 10;

				for (int i = 0; i < size; i++)
					tmp *= 10;

				int tmp2 = page % tmp;

				numCount[num] += page / tmp + 1 - (tmp2 < (num* tmp / 10) ? 0 : 1);
			}
			break;
		}
	}

	for (int i = 0; i < 10; i++)
		cout << numCount[i] << " ";
}

void Test4()
{

}

int main()
{
	//Test1();
	//Test2();
	//Test3();

	return 0;
}
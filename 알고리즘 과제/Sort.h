#pragma once

#include<chrono>

using std::chrono::system_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

class Sort
{
protected:
	void Swap(int& num1, int& num2)
	{
		int tmp = num1;
		num1 = num2;
		num2 = tmp;
	}

public:
	virtual void Sorting(int* nums, int count) = 0;

	float Run(int* nums, int count)
	{
		system_clock::time_point start = system_clock::now();

		Sorting(nums, count);

		system_clock::time_point end = system_clock::now();
		microseconds micro = duration_cast<microseconds>(end - start);

		return (float)micro.count() / 1000;
	}
};
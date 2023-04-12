#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>

using namespace std;

bool IsPrimeNumber(int num)
{
	if (num == 1)
		return false;

	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
			return false;
	}

	return true;
}

void SortUpper(vector<int> &nums)
{
	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = i; j < nums.size(); j++)
		{
			if (nums[i] > nums[j])
			{
				int tmp = nums[i];
				nums[i] = nums[j];
				nums[j] = tmp;
			}
		}
	}
}
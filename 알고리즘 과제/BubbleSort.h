#pragma once

#include "Sort.h"

class BubbleSort : public Sort
{
public:
	void Sorting(int* nums, int count)
	{
		for (int i = count - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums[j] > nums[j + 1])
					Swap(nums[j], nums[j + 1]);
			}
		}
	}
};
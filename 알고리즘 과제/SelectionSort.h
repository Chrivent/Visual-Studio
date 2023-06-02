#pragma once

#include "Sort.h"

class SelectionSort : public Sort
{
public:
	void Sorting(int* nums, int count)
	{
		for (int i = 0; i < count - 1; i++)
		{
			int minIndex = i;

			for (int j = i + 1; j < count; j++)
			{
				if (nums[j] < nums[minIndex])
					minIndex = j;
			}

			if (i != minIndex)
				Swap(nums[i], nums[minIndex]);
		}
	}
};
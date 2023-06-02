#pragma once

#include "Sort.h"

class InsertionSort : public Sort
{
public:
	void Sorting(int* nums, int count)
	{
        for (int i = 1; i < count; i++)
        {
            int key = nums[i];

            int j;
            for (j = i - 1; j >= 0 && nums[j] > key; j--)
                nums[j + 1] = nums[j];

            nums[j + 1] = key;
        }
	}
};
#pragma once
 
#include "Sort.h"

class ShellSort : public Sort
{
private:
    void ShellSorting(int* nums, int first, int last, int gap)
    {
        for (int i = first + gap; i <= last; i = i + gap)
        {
            int key = nums[i];

            int j;
            for (j = i - gap; j >= first && nums[j] > key; j = j - gap)
                nums[j + gap] = nums[j];

            nums[j + gap] = key;
        }
    }

public:
	void Sorting(int* nums, int count)
	{
        for (int gap = count / 2; gap > 0; gap = gap / 2)
        {
            if ((gap % 2) == 0)
                gap++;

            for (int i = 0; i < gap; i++)
                ShellSorting(nums, i, count - 1, gap);
        }
	}
};
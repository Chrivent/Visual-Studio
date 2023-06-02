#pragma once

#include "Sort.h"

class QuickSort : public Sort
{
private:
	int Partition(int* nums, int left, int right)
	{
		int low = left;
		int high = right + 1;
		int pivot = nums[left];

		do
		{
			do
				low++;
			while (low <= right && nums[low] < pivot);

			do
				high--;
			while (high >= left && nums[high] > pivot);

			if (low < high)
				Swap(nums[low], nums[high]);
		}
		while (low < high);

		Swap(nums[left], nums[high]);

		return high;
	}

	void QuickSorting(int* nums, int left, int right)
	{
		if (left < right)
		{
			int q = Partition(nums, left, right);

			QuickSorting(nums, left, q - 1);
			QuickSorting(nums, q + 1, right);
		}
	}

public:
	void Sorting(int* nums, int count)
	{
		QuickSorting(nums, 0, count - 1);
	}
};
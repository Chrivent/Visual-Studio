#pragma once

#include "Sort.h"

class MergeSort : public Sort
{
private:
	int* sorted;

	void Merge(int* nums, int left, int mid, int right)
	{
		int i = left;
		int j = mid + 1;
		int k = left;

		while (i <= mid && j <= right)
		{
			if (nums[i] <= nums[j])
				sorted[k++] = nums[i++];
			else
				sorted[k++] = nums[j++];
		}

		if (i > mid)
		{
			for (int l = j; l <= right; l++)
				sorted[k++] = nums[l];
		}
		else
		{
			for (int l = i; l <= mid; l++)
				sorted[k++] = nums[l];
		}

		for (int l = left; l <= right; l++)
			nums[l] = sorted[l];
	}

	void MergeSorting(int* nums, int left, int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2;

			MergeSorting(nums, left, mid);
			MergeSorting(nums, mid + 1, right);
			Merge(nums, left, mid, right);
		}
	}

public:
	MergeSort() : sorted(nullptr) {}

	void Sorting(int* nums, int count)
	{
		sorted = new int[count];

		MergeSorting(nums, 0, count - 1);

		delete[] sorted;
	}
};
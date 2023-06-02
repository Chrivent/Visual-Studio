#pragma once

#include<iostream>
#include<string>
#include "SelectionSort.h"
#include "BubbleSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"

using std::cout;
using std::endl;
using std::to_string;

class SortingPerformanceTest
{
private:
	int count;

	int* selectionNums = new int[count];
	int* bubbleNums = new int[count];
	int* insertionNums = new int[count];
	int* mergeNums = new int[count];
	int* quickNums = new int[count];
	int* shellNums = new int[count];

	Sort* selectionSort;
	Sort* bubbleSort;
	Sort* insertionSort;
	Sort* mergeSort;
	Sort* quickSort;
	Sort* shellSort;

	void DrawPerformance()
	{
		cout << "�������� : " << selectionSort->Run(selectionNums, count) << " ms" << endl;
		cout << "�������� : " << bubbleSort->Run(bubbleNums, count) << " ms" << endl;
		cout << "�������� : " << insertionSort->Run(insertionNums, count) << " ms" << endl;
		cout << "�պ����� : " << mergeSort->Run(mergeNums, count) << " ms" << endl;
		cout << "������ : " << quickSort->Run(quickNums, count) << " ms" << endl;
		cout << "������ : " << shellSort->Run(shellNums, count) << " ms" << endl;
	}

	void SetNumsRandom()
	{
		for (int i = 0; i < count; i++)
		{
			int tmp = rand();

			selectionNums[i] = tmp;
			bubbleNums[i] = tmp;
			insertionNums[i] = tmp;
			mergeNums[i] = tmp;
			quickNums[i] = tmp;
			shellNums[i] = tmp;
		}
	}

	void SetNumsAscending()
	{
		for (int i = 0; i < count; i++)
		{
			int tmp = i + 1;

			selectionNums[i] = tmp;
			bubbleNums[i] = tmp;
			insertionNums[i] = tmp;
			mergeNums[i] = tmp;
			quickNums[i] = tmp;
			shellNums[i] = tmp;
		}
	}

	void SetNumsDescending()
	{
		for (int i = 0; i < count; i++)
		{
			int tmp = count - i;

			selectionNums[i] = tmp;
			bubbleNums[i] = tmp;
			insertionNums[i] = tmp;
			mergeNums[i] = tmp;
			quickNums[i] = tmp;
			shellNums[i] = tmp;
		}
	}

	void AllocationNums(int count)
	{
		this->count = count;

		selectionNums = new int[count];
		bubbleNums = new int[count];
		insertionNums = new int[count];
		mergeNums = new int[count];
		quickNums = new int[count];
		shellNums = new int[count];
	}

	void DeleteNums()
	{
		delete[] selectionNums;
		delete[] bubbleNums;
		delete[] insertionNums;
		delete[] mergeNums;
		delete[] quickNums;
		delete[] shellNums;
	}

	void Release()
	{
		DeleteNums();

		delete selectionSort;
		delete bubbleSort;
		delete insertionSort;
		delete mergeSort;
		delete quickSort;
		delete shellSort;
	}

public:
	SortingPerformanceTest()
	{
		srand((unsigned int)time(NULL));

		AllocationNums(10);

		selectionSort = new SelectionSort;
		bubbleSort = new BubbleSort;
		insertionSort = new InsertionSort;
		mergeSort = new MergeSort;
		quickSort = new QuickSort;
		shellSort = new ShellSort;
	}

	void SetCount(int count)
	{
		DeleteNums();
		AllocationNums(count);
	}

	void DrawPerformanceByRandom()
	{
		SetNumsRandom();

		cout << "==== ���� ���� (" + to_string(count) + "��) ====" << endl;
		DrawPerformance();
		cout << endl;
	}

	void DrawPerformanceByAscending()
	{
		SetNumsAscending();

		cout << "==== �������� ���� (" + to_string(count) + "��) ====" << endl;
		DrawPerformance();
		cout << endl;
	}

	void DrawPerformanceByDescending()
	{
		SetNumsDescending();

		cout << "==== �������� ���� (" + to_string(count) + "��) ====" << endl;
		DrawPerformance();
		cout << endl;
	}

	~SortingPerformanceTest()
	{
		Release();
	}
};
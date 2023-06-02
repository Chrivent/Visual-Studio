#include "SortingPerformanceTest.h"

int main()
{
	SortingPerformanceTest sortingPerformanceTest;

	sortingPerformanceTest.SetCount(3000);
	sortingPerformanceTest.DrawPerformanceByRandom();
	sortingPerformanceTest.SetCount(5000);
	sortingPerformanceTest.DrawPerformanceByRandom();
	sortingPerformanceTest.SetCount(10000);
	sortingPerformanceTest.DrawPerformanceByRandom();

	sortingPerformanceTest.SetCount(3000);
	sortingPerformanceTest.DrawPerformanceByAscending();
	sortingPerformanceTest.SetCount(5000);
	sortingPerformanceTest.DrawPerformanceByAscending();
	sortingPerformanceTest.SetCount(10000);
	sortingPerformanceTest.DrawPerformanceByAscending();

	sortingPerformanceTest.SetCount(3000);
	sortingPerformanceTest.DrawPerformanceByDescending();
	sortingPerformanceTest.SetCount(5000);
	sortingPerformanceTest.DrawPerformanceByDescending();
	sortingPerformanceTest.SetCount(10000);
	sortingPerformanceTest.DrawPerformanceByDescending();

	return 0;
}
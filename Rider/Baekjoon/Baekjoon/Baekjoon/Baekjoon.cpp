#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>

using namespace std;

struct Edge
{
	int start;
	int end;
};

int main()
{
	int scoreCount;
	cin >> scoreCount;

	vector<int> scores(scoreCount);
	for (int& score : scores)
		cin >> score;

	int removeCount, range;
	cin >> removeCount >> range;

	vector<int> a;
	for (int i = 0; i < removeCount; i++)
	{
		int maxV = 0;
		int maxIndex = -1;
		for (int j = 0; j < range; j++)
		{
			if (maxV < scores[j])
			{
				maxV = scores[j];
				maxIndex = j;
			}
		}

		a.push_back(scores[maxIndex]);

		int minV = 999999999;
		int minIndex = -1;
		for (int j = scores.size() - 1; j >= scores.size() - range; j--)
		{
			if (minV > scores[j])
			{
				minV = scores[j];
				minIndex = j;
			}
		}

		a.push_back(scores[minIndex]);

		scores.erase(scores.begin() + maxIndex);
		scores.erase(scores.begin() + minIndex - 1);
	}

	int sum = 0;
	for (auto score : a)
	{
		sum += score;
	}

	cout << sum;
	
	return 0;
}

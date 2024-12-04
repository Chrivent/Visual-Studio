#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<set>

using namespace std;

struct Line
{
	int u;
	int v;
	int w;
};

int main()
{
	int v, e, k;
	cin >> v >> e >> k;

	vector<Line> lines;
	for (int i = 0; i < e; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		lines.push_back({ u, v, w });
	}



	return 0;
}
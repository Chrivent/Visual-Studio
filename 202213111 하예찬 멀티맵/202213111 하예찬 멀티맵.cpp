#include<iostream>
#include<map>
#include<string>

using namespace std;

int main()
{
	int count;
	string myTeamName;
	cin >> count >> myTeamName;

	multimap<string, string> baseballTeams;
	for (int i = 0; i < count; i++)
	{
		string name, teamName;
		cin >> name >> teamName;
		baseballTeams.insert({ teamName, name });
	}

	multimap<string, string>::iterator beginiter = baseballTeams.lower_bound(myTeamName);
	multimap<string, string>::iterator enditer = baseballTeams.upper_bound(myTeamName);

	cout << myTeamName << endl;
	for (multimap<string, string>::iterator iter = beginiter; iter != enditer; ++iter)
		cout << iter->second << endl;

	return 0;
}
#include<iostream>

using namespace std;

template<typename T>
int Comparison(T data1, T data2)
{
	if (data1 > data2)
		return 0;
	else if (data1 < data2)
		return 1;
	
	return 2;
}

int main()
{
	int a, b;

	cin >> a;
	cin >> b;

	cout << Comparison(a, b) << endl;

	return 0;
}
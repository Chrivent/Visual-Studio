#include<iostream>

using namespace std;

int fibonacci(int n)
{
	if (n <= 2)
		return 1;

	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	int input;

	cin >> input;

	for (int i = 1; i <= input; i++)
		cout << fibonacci(i) << " ";

	return 0;
}
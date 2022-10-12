#include<iostream>
#include<vector>
#include<conio.h>
#include<fstream>
#include<string>

using namespace std;

int RandNum(int min, int max)
{
	static bool tmp = false;

	if (tmp == false)
	{
		srand((unsigned int)time(NULL));
		tmp = true;
	}

	while (true)
	{
		int num = rand() % max;
		if (num >= min)
			return num;
	}
}

class Account
{
private:
	char* name;
	string socialSecurityNumber;
	int money;
	int accountNumber;

public:
	Account(char* name, string socialSecurityNumber, int money, int accountNumber)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->socialSecurityNumber = socialSecurityNumber;
		this->money = money;
		this->accountNumber = accountNumber;
	}

	Account(const Account &account)
	{
		this->name = new char[strlen(account.name) + 1];
		strcpy(this->name, account.name);
		this->socialSecurityNumber = account.socialSecurityNumber;
		this->money = account.money;
		this->accountNumber = account.accountNumber;
	}

	void AddMoney(int money)
	{
		this->money += money;
	}

	void SubtractMoney(int money)
	{
		this->money -= money;
	}

	char* GetName()
	{
		return name;
	}

	string GetSocialSecurityNumber()
	{
		return socialSecurityNumber;
	}

	int GetMoney()
	{
		return money;
	}

	int GetAccountNumber()
	{
		return accountNumber;
	}
};

class Bank
{
private:
	vector<Account*> accounts;

	int scene;

public:
	Bank()
	{
		scene = 0;
	}

	void SelectMenu()
	{
		cout << "----Menu----" << endl;
		cout << "1. 계좌개설" << endl;
		cout << "2. 입금" << endl;
		cout << "3. 출금" << endl;
		cout << "4. 전체고객 잔액조회" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택 : ";
		cin >> scene;
	}

	void CreateFile(char* name, string socialSecurityNumber, int money, int accountNumber)
	{
		string tmp(name);

		ofstream file(tmp + "님의 계좌.txt");

		file << "계좌번호 : " << accountNumber << endl;
		file << "이름 : " << name << endl;
		file << "주민번호 : " << socialSecurityNumber << endl;
		file << "잔액 : " << money;

		file.close();
	}

	void CreateAccount()
	{
		char name[20];
		string socialSecurityNumber;
		int money;
		int tmp;
		int accountNumber;

		cout << "[계좌개설]" << endl;
		cout << "이름 : ";
		cin >> name;

		cout << "주민번호 : ";
		cin >> socialSecurityNumber;

		cout << "입금액 : ";
		cin >> money;

		accountNumber = RandNum(10000, 100000);

		Account account(name, socialSecurityNumber, money, accountNumber);

		accounts.push_back(new Account(account));

		CreateFile(name, socialSecurityNumber, money, accountNumber);

		cout << "계좌개설이 완료되었습니다.";

		tmp = _getch();

		scene = 0;
	}

	void AddMoney()
	{
		string socialSecurityNumber;
		int money;
		int tmp;

		cout << "[입금]" << endl;
		cout << "주민번호 : ";
		cin >> socialSecurityNumber;

		Account* account = GetAccountBySocialSecurityNumber(socialSecurityNumber);

		if (account != nullptr)
		{
			cout << "이름: " << account->GetName() << endl;

			cout << "입금액 : ";
			cin >> money;

			account->AddMoney(money);

			CreateFile(account->GetName(), socialSecurityNumber, account->GetMoney(), account->GetAccountNumber());

			cout << "입금이 완료되었습니다." << endl;
			cout << account->GetName() << "님의 잔액은 " << account->GetMoney() << "원입니다.";

			tmp = _getch();

			scene = 0;
		}
		else
		{
			cout << "계좌가 없습니다.";

			tmp = _getch();
		}
	}

	void SubtractMoney()
	{
		string socialSecurityNumber;
		int money;
		int tmp;

		cout << "[출금]" << endl;
		cout << "주민번호 : ";
		cin >> socialSecurityNumber;

		Account* account = GetAccountBySocialSecurityNumber(socialSecurityNumber);

		if (account != nullptr)
		{
			cout << "이름 : " << account->GetName() << endl;

			bool pass = false;

			while (pass == false)
			{
				cout << "출금액 : ";
				cin >> money;

				if (account->GetMoney() < money)
					cout << "잔액이 부족합니다." << endl;
				else
					pass = true;
			}

			account->SubtractMoney(money);

			CreateFile(account->GetName(), socialSecurityNumber, account->GetMoney(), account->GetAccountNumber());

			cout << "출금이 완료되었습니다." << endl;
			cout << account->GetName() << "님의 잔액은 " << account->GetMoney() << "원입니다.";

			tmp = _getch();

			scene = 0;
		}
		else
		{
			cout << "계좌가 없습니다.";

			tmp = _getch();
		}
	}

	void ShowWholeAccount()
	{
		int tmp;

		for (int i = 0; i < accounts.size(); i++)
		{
			if (accounts[i] != nullptr)
			{
				string socialSecurityNumber = accounts[i]->GetSocialSecurityNumber();
				string name = accounts[i]->GetName();
				int money = accounts[i]->GetMoney();
				int accountNumber = accounts[i]->GetAccountNumber();

				cout << "[계좌정보]" << endl;
				cout << "계좌번호 : " << accountNumber << endl;
				cout << "주민번호 : " << socialSecurityNumber << endl;
				cout << "이름 : " << name << endl;
				cout << "잔액 : " << money << endl << endl;
			}
		}

		tmp = _getch();

		scene = 0;
	}

	Account* GetAccountBySocialSecurityNumber(string socialSecurityNumber)
	{
		for (int i = 0; i < accounts.size(); i++)
		{
			if (accounts[i] != nullptr && accounts[i]->GetSocialSecurityNumber() == socialSecurityNumber)
				return accounts[i];
		}

		return nullptr;
	}

	bool Update()
	{
		system("cls");

		switch (scene)
		{
		case 0:
			SelectMenu();
			break;

		case 1:
			CreateAccount();
			break;

		case 2:
			AddMoney();
			break;

		case 3:
			SubtractMoney();
			break;

		case 4:
			ShowWholeAccount();
			break;

		case 5:
			cout << "은행을 이용해주셔서 감사합니다." << endl;
			return false;
		}

		return true;
	}

	~Bank()
	{
		for (int i = 0; i < accounts.size(); i++)
		{
			if (accounts[i] != nullptr)
			{
				delete accounts[i];
				accounts[i] = nullptr;
			}
		}
	}
};

int main()
{
	Bank* bank;
	bank = new Bank;

	while (bank->Update());

	delete bank;
	bank = nullptr;

	return 0;
}
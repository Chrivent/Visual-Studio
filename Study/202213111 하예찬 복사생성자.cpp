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
		cout << "1. ���°���" << endl;
		cout << "2. �Ա�" << endl;
		cout << "3. ���" << endl;
		cout << "4. ��ü�� �ܾ���ȸ" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "���� : ";
		cin >> scene;
	}

	void CreateFile(char* name, string socialSecurityNumber, int money, int accountNumber)
	{
		string tmp(name);

		ofstream file(tmp + "���� ����.txt");

		file << "���¹�ȣ : " << accountNumber << endl;
		file << "�̸� : " << name << endl;
		file << "�ֹι�ȣ : " << socialSecurityNumber << endl;
		file << "�ܾ� : " << money;

		file.close();
	}

	void CreateAccount()
	{
		char name[20];
		string socialSecurityNumber;
		int money;
		int tmp;
		int accountNumber;

		cout << "[���°���]" << endl;
		cout << "�̸� : ";
		cin >> name;

		cout << "�ֹι�ȣ : ";
		cin >> socialSecurityNumber;

		cout << "�Աݾ� : ";
		cin >> money;

		accountNumber = RandNum(10000, 100000);

		Account account(name, socialSecurityNumber, money, accountNumber);

		accounts.push_back(new Account(account));

		CreateFile(name, socialSecurityNumber, money, accountNumber);

		cout << "���°����� �Ϸ�Ǿ����ϴ�.";

		tmp = _getch();

		scene = 0;
	}

	void AddMoney()
	{
		string socialSecurityNumber;
		int money;
		int tmp;

		cout << "[�Ա�]" << endl;
		cout << "�ֹι�ȣ : ";
		cin >> socialSecurityNumber;

		Account* account = GetAccountBySocialSecurityNumber(socialSecurityNumber);

		if (account != nullptr)
		{
			cout << "�̸�: " << account->GetName() << endl;

			cout << "�Աݾ� : ";
			cin >> money;

			account->AddMoney(money);

			CreateFile(account->GetName(), socialSecurityNumber, account->GetMoney(), account->GetAccountNumber());

			cout << "�Ա��� �Ϸ�Ǿ����ϴ�." << endl;
			cout << account->GetName() << "���� �ܾ��� " << account->GetMoney() << "���Դϴ�.";

			tmp = _getch();

			scene = 0;
		}
		else
		{
			cout << "���°� �����ϴ�.";

			tmp = _getch();
		}
	}

	void SubtractMoney()
	{
		string socialSecurityNumber;
		int money;
		int tmp;

		cout << "[���]" << endl;
		cout << "�ֹι�ȣ : ";
		cin >> socialSecurityNumber;

		Account* account = GetAccountBySocialSecurityNumber(socialSecurityNumber);

		if (account != nullptr)
		{
			cout << "�̸� : " << account->GetName() << endl;

			bool pass = false;

			while (pass == false)
			{
				cout << "��ݾ� : ";
				cin >> money;

				if (account->GetMoney() < money)
					cout << "�ܾ��� �����մϴ�." << endl;
				else
					pass = true;
			}

			account->SubtractMoney(money);

			CreateFile(account->GetName(), socialSecurityNumber, account->GetMoney(), account->GetAccountNumber());

			cout << "����� �Ϸ�Ǿ����ϴ�." << endl;
			cout << account->GetName() << "���� �ܾ��� " << account->GetMoney() << "���Դϴ�.";

			tmp = _getch();

			scene = 0;
		}
		else
		{
			cout << "���°� �����ϴ�.";

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

				cout << "[��������]" << endl;
				cout << "���¹�ȣ : " << accountNumber << endl;
				cout << "�ֹι�ȣ : " << socialSecurityNumber << endl;
				cout << "�̸� : " << name << endl;
				cout << "�ܾ� : " << money << endl << endl;
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
			cout << "������ �̿����ּż� �����մϴ�." << endl;
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
#include<iostream>
#include<string>

using namespace std;

class IPlayer
{
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
};

class IWeapon
{
public:
	virtual void Fire() = 0;
	virtual string GetWeaponName() = 0;
};

class Player : public IPlayer
{
protected:
	string name;
	IWeapon* weapon;

public:
	Player()
	{
		weapon = nullptr;
	}

	string GetName()
	{
		return name;
	}

	void Move()
	{
		cout << name << " �̵�" << endl;
	}

	void Attack()
	{
		if (weapon != nullptr)
			weapon->Fire();
	}

	virtual ~Player()
	{
		if (weapon != nullptr)
			delete weapon;
	}
};

class Weapon : public IWeapon
{
protected:
	string name;

public:
	void Fire()
	{
		cout << GetWeaponName() << " �߻�" << endl;
	}

	string GetWeaponName()
	{
		return name;
	}
};

class GunWeapon : public Weapon
{
public:
	GunWeapon()
	{
		name = "��";
	}
};

class RocketWeapon : public Weapon
{
public:
	RocketWeapon()
	{
		name = "����";
	}
};

class LaserWeapon : public Weapon
{
public:
	LaserWeapon()
	{
		name = "������";
	}
};

class Engineer : public Player
{
public:
	Engineer()
	{
		name = "�����Ͼ�";
		weapon = new GunWeapon();
	}
};

class Assault : public Player
{
public:
	Assault()
	{
		name = "���Ʈ";
		weapon = new LaserWeapon();
	}
};

class Medic : public Player
{
public:
	Medic()
	{
		name = "�޵�";
		weapon = new RocketWeapon();
	}
};

int main()
{
	Player* players[3];

	players[0] = new Engineer();
	players[1] = new Assault();
	players[2] = new Medic();

	for (int i = 0; i < sizeof(players) / sizeof(Player*); i++)
	{
		players[i]->Move();
		players[i]->Attack();
	}

	return 0;
}
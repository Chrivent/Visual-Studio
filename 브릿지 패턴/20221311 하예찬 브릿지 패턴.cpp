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
		cout << name << " 이동" << endl;
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
		cout << GetWeaponName() << " 발사" << endl;
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
		name = "총";
	}
};

class RocketWeapon : public Weapon
{
public:
	RocketWeapon()
	{
		name = "로켓";
	}
};

class LaserWeapon : public Weapon
{
public:
	LaserWeapon()
	{
		name = "레이저";
	}
};

class Engineer : public Player
{
public:
	Engineer()
	{
		name = "엔지니어";
		weapon = new GunWeapon();
	}
};

class Assault : public Player
{
public:
	Assault()
	{
		name = "어썰트";
		weapon = new LaserWeapon();
	}
};

class Medic : public Player
{
public:
	Medic()
	{
		name = "메딕";
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
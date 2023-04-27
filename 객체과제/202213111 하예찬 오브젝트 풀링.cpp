#include<iostream>

using namespace std;

class GameObject
{

};

class GameObjectPool
{
private:
	int objectCount;
	int cellCount;

	GameObject** gameObjects;

	int loadedCount;

public:
	GameObjectPool(int cellCount) : cellCount(cellCount)
	{
		objectCount = cellCount;

		gameObjects = new GameObject*[objectCount];

		for (int i = 0; i < objectCount; i++)
			gameObjects[i] = new GameObject;

		loadedCount = 0;
	}

	int GetObjectCount()
	{
		return objectCount;
	}

	int GetUsingCount()
	{
		return loadedCount;
	}

	GameObject* Pop()
	{
		if (loadedCount >= objectCount)
		{
			GameObject** tmp = new GameObject*[objectCount + cellCount];

			for (int i = 0; i < objectCount; i++)
				tmp[i] = gameObjects[i];

			delete[] gameObjects;

			for (int i = objectCount; i < objectCount + cellCount; i++)
				tmp[i] = new GameObject;

			gameObjects = tmp;

			objectCount += cellCount;
		}

		GameObject* obj = gameObjects[loadedCount];

		gameObjects[loadedCount] = nullptr;
		loadedCount++;

		return obj;
	}

	void Push(GameObject* gameObject)
	{
		gameObjects[--loadedCount] = gameObject;
	}

	~GameObjectPool()
	{
		for (int i = 0; i < objectCount; i++)
		{
			if (gameObjects[i] != nullptr)
				delete gameObjects[i];
		}

		delete[] gameObjects;
	}
};

int main()
{
	cout << "���� �� �⺻ ������Ʈ ����" << endl << endl;

	GameObjectPool gameObjectPool(3);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "�ϳ��� ������ ��" << endl << endl;

	GameObject* a = gameObjectPool.Pop();

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "�ٽ� ���� ��" << endl << endl;

	gameObjectPool.Push(a);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "cell �������� ���� ���� ���� �� (cell ���� : 3��, ���� ���� : 4��)" << endl << endl;

	GameObject* b = gameObjectPool.Pop();
	GameObject* c = gameObjectPool.Pop();
	GameObject* d = gameObjectPool.Pop();
	GameObject* e = gameObjectPool.Pop();

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "3���� �ٽ� ��ȯ�� ��" << endl << endl;

	gameObjectPool.Push(b);
	gameObjectPool.Push(c);
	gameObjectPool.Push(d);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	return 0;
}
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
	cout << "생성 시 기본 오브젝트 갯수" << endl << endl;

	GameObjectPool gameObjectPool(3);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "하나를 꺼냈을 때" << endl << endl;

	GameObject* a = gameObjectPool.Pop();

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "다시 넣을 때" << endl << endl;

	gameObjectPool.Push(a);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "cell 갯수보다 많은 양을 꺼낼 때 (cell 갯수 : 3개, 꺼낸 갯수 : 4개)" << endl << endl;

	GameObject* b = gameObjectPool.Pop();
	GameObject* c = gameObjectPool.Pop();
	GameObject* d = gameObjectPool.Pop();
	GameObject* e = gameObjectPool.Pop();

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	cout << "3개를 다시 반환할 때" << endl << endl;

	gameObjectPool.Push(b);
	gameObjectPool.Push(c);
	gameObjectPool.Push(d);

	cout << "Object Count : " << gameObjectPool.GetObjectCount() << endl;
	cout << "Using Count : " << gameObjectPool.GetUsingCount() << endl;
	cout << endl << endl;

	return 0;
}
#include <iostream>

using namespace std;

struct node
{
	int data;
	node* next;

	node(int item) :data(item), next(nullptr) {}
};

class Queue
{
private:
	int size;
	node* front;
	node* rear;

public:
	Queue() : front(nullptr), rear(nullptr), size(0) {}

	void Push(int item)
	{
		node* InNode = new node(item);

		if (size == 0)
		{
			front = InNode;
			rear = InNode;
		}
		else
		{
			rear->next = InNode;
			rear = InNode;
		}

		size++;
	}

	void Pop()
	{
		if (!Empty())
		{
			node* delNode = front;

			front = front->next;

			delete delNode;

			size--;
		}
	}

	int Front()
	{
		return Empty() ? -1 : front->data;
	}

	bool Empty()
	{
		return (size == 0);
	}

	int Size()
	{
		return size;
	}

	~Queue()
	{
		while (!Empty())
			Pop();
	}
};

int main()
{
	Queue que;

	for (int i = 0; i < 10; i++)
		que.Push(i);

	cout << que.Front() << "size : " << que.Size() << endl;

	que.Pop();

	cout << que.Front() << "size : " << que.Size() << endl;

	for (int i = 0; i < que.Size(); i++)
		que.Pop();

	return 0;
}
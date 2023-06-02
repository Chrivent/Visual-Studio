#include<iostream>

using namespace std;

class Heap
{
private:
	int capacity;
	int count;
	int* items;

	void HeapifyUp()
	{
		int current = count - 1;
		int parent = (current - 1) / 2;

		while (current != 0 && items[current] > items[parent])
		{
			swap(items[current], items[parent]);

			current = parent;
			parent = (current - 1) / 2;
		}
	}

	void HeapifyDown()
	{
		int parent = 0;
		int current = parent * 2 + 1;

		while (current < count)
		{
			if (current + 1 < count - 1 && items[current] < items[current + 1])
				current++;

			swap(items[parent], items[current]);

			parent = current;
			current = parent * 2 + 1;
		}
	}

public:
	Heap(int capacity) : capacity(capacity), count(0)
	{
		items = new int[capacity];
	}

	void Insert(int value)
	{
		if (count >= capacity)
			return;

		count++;

		items[count - 1] = value;

		HeapifyUp();
	}

	int Remove()
	{
		if (count == 0)
			return -1;

		int tmp = items[0];

		items[0] = items[count - 1];

		HeapifyDown();

		count--;

		return tmp;
	}

	~Heap()
	{
		delete[] items;
	}
};

int main()
{
	int count = 5;

	Heap* heap = new Heap(count);

	heap->Insert(10);
	heap->Insert(30);
	heap->Insert(50);
	heap->Insert(40);
	heap->Insert(20);

	for (int i = 0; i < count; i++)
		cout << heap->Remove() << endl;

	delete heap;

	return 0;
}
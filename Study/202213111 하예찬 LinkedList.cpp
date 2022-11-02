#include <iostream>

using namespace std;

struct Node
{
	int data = 0;

	Node* prev = nullptr;
	Node* next = nullptr;

	Node() {}
	Node(int data) : data(data) {}
};

class DoubleLinkedList
{
private:
	Node* head;

	int count;

public:
	DoubleLinkedList()
	{
		head = new Node();

		count = 0;
	}

	void InsertNode(int pos, int data)
	{
		if (pos < 0 || pos > count)
			return;

		Node* posNode = new Node(data);
		Node* prevNode = head;

		for (int i = 0; i < pos; i++)
			prevNode = prevNode->next;

		posNode->prev = prevNode;
		prevNode->next = posNode;

		Node* nextNode = prevNode->next;

		if (nextNode != nullptr)
		{
			posNode->next = nextNode;
			nextNode->prev = posNode;
		}

		count++;
	}

	void DeleteNode(int pos)
	{
		if (pos < 0 || pos >= count)
			return;

		Node* prevNode = head;

		for (int i = 0; i < pos; i++)
			prevNode = prevNode->next;

		Node* posNode = prevNode->next;
		Node* nextNode = posNode->next;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		delete posNode;

		posNode = nullptr;

		count--;
	}

	int GetLength()
	{
		return count;
	}

	~DoubleLinkedList()
	{
		Node* prevNode = head;

		for (int i = 0; i <= count; i++)
		{
			Node* posNode = prevNode->next;

			delete prevNode;

			prevNode = posNode;
		}
	}
};

int main()
{

}
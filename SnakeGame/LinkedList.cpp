#include "LinkedList.h"

Node::Node()
{
	next = nullptr;
}

Node::Node(Position position)
{
	this->position = position;

	next = nullptr;
}

LinkedList::LinkedList()
{
	head = new Node;

	length = 0;
}

void LinkedList::Append(Position position)
{
	Node* prevNode = head;

	for (int i = 0; i < length; i++)
		prevNode = prevNode->next;

	Node* lastNode = new Node(position);

	prevNode->next = lastNode;

	length++;
}

void LinkedList::Insert(int index, Position position)
{
	if (index < 0 || index > length)
		return;
	else
	{
		Node* prevNode = head;

		for (int i = 0; i < index; i++)
			prevNode = prevNode->next;

		Node* nextNode = prevNode->next;
		Node* indexNode = new Node(position);

		prevNode->next = indexNode;
		indexNode->next = nextNode;

		length++;
	}
}

Node* LinkedList::GetNode(int index)
{
	if (index < 0 || index >= length)
		return nullptr;
	else
	{
		Node* prevNode = head;

		for (int i = 0; i < index; i++)
			prevNode = prevNode->next;

		Node* indexNode = prevNode->next;

		return indexNode;
	}
}

void LinkedList::Remove(int index)
{
	if (index < 0 || index >= length)
		return;
	else
	{
		Node* prevNode = head;

		for (int i = 0; i < index; i++)
			prevNode = prevNode->next;

		Node* indexNode = prevNode->next;
		Node* nextNode = indexNode->next;

		delete indexNode;

		prevNode->next = nextNode;

		length--;
	}
}

void LinkedList::RemoveAll()
{
	if (length == 0)
		return;

	Node* curNode = head->next;

	for (int i = 0; i < length; i++)
	{
		Node* nextNode = curNode->next;

		delete curNode;

		curNode = nextNode;
	}

	length = 0;
}

int LinkedList::GetLength()
{
	return length;
}

LinkedList::~LinkedList()
{
	RemoveAll();

	delete head;

	head = nullptr;
}
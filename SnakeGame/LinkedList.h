#pragma once

#include "Body.h"

struct Node : public Body
{
	Node* next;

	Node();
	Node(Position position);
};

class LinkedList
{
private:
	Node* head;
	int length;

public:
	LinkedList();

	void Append(Position position);
	void Insert(int index, Position position);
	Node* GetNode(int index);
	void Remove(int index);
	void RemoveAll();
	int GetLength();

	~LinkedList();
};
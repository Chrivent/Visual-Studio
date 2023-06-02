#pragma once

class Node
{
public:
	int data;

	Node* left;
	Node* right;

	Node(int data) : data(data), left(nullptr), right(nullptr) {}
	~Node() { if (left != nullptr) delete left; if (right != nullptr) delete right; }
};
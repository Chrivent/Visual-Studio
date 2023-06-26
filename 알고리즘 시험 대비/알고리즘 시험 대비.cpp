#include <iostream>

using namespace std;

namespace SearchAlgorithm
{
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* next;

		Node(T data) : data(data), next(nullptr) {}
	};

	template <typename T>
	class LinearSearch
	{
	public:
		T Search(T arr[], int count, T target)
		{
			for (int i = 0; i < count; i++)
			{
				if (arr[i] == target)
					return i;
			}

			return -1;
		}

		Node<T>* Search(Node<T>* head, T target)
		{
			Node<T>* node = head;

			while (node != nullptr)
			{
				if (node->data == target)
					return node;
				else
					node = node->next;
			}

			return nullptr;
		}

		int MoveToFront(T arr[], int count, T target)
		{
			for (int i = 0; i < count; i++)
			{
				if (arr[i] == target)
				{
					for (int j = i - 1; j >= 0; j--)
						arr[j + 1] = arr[j];

					arr[0] = target;

					return 0;
				}
			}

			return -1;
		}

		Node<T>* MoveToFront(Node<T>* head, T target)
		{
			Node<T>* node = head;
			Node<T>* prev = nullptr;
			Node<T>* match = nullptr;

			while (node != nullptr)
			{
				if (node->data == target)
				{
					match = node;

					if (prev != nullptr)
					{
						prev->next = node->next;
						node->next = head;
						head = node;
					}

					break;
				}
				else
				{
					prev = node;
					node = node->next;
				}
			}

			return match;
		}

		int Transpose(T arr[], int count, T target)
		{
			for (int i = 0; i < count; i++)
			{
				if (arr[i] == target)
				{
					if (i == 0)
						return true;

					arr[i] = arr[i - 1];
					arr[i - 1] = target;

					return i - 1;
				}
			}

			return -1;
		}

		Node<T>* Transpose(Node<T>* head, T target)
		{
			Node<T>* node = head;
			Node<T>* prev = nullptr;
			Node<T>* pprev = nullptr;
			Node<T>* match = nullptr;

			while (node != nullptr)
			{
				if (node->data == target)
				{
					match = node;

					if (prev != nullptr)
					{
						if (pprev != nullptr)
							pprev->next = node;
						else
							head = node;

						prev->next = node->next;
						node->next = prev;
					}

					break;
				}
				else
				{
					if (prev != nullptr)
						pprev = prev;

					prev = node;
					node = node->next;
				}
			}

			return match;
		}
	};

	template <typename T>
	class BinarySearch
	{
	public:
		int Search(T arr[], T target, int low, int high)
		{
			if (low > high)
				return -1;
			else
			{
				int mid = (low + high) / 2;

				if (arr[mid] == target)
					return mid;
				else if (arr[mid] > target)
					return Search(arr, target, low, mid - 1);
				else
					return Search(arr, target, mid + 1, high);
			}
		}

		int Search(T arr[], T target, int count)
		{
			int begin = 0;
			int end = count - 1;

			while (begin <= end)
			{
				int mid = (begin + end) / 2;

				if (arr[mid] == target)
					return mid;
				else if (arr[mid] > target)
					end = mid - 1;
				else
					begin = mid + 1;
			}

			return -1;
		}
	};

	template <typename T>
	class LinearInterpolationSearch
	{
	public:
		int Search(T arr[], T target, int low, int high)
		{
			int mid;
			T denominator;

			if (low > high)
				return -1;
			else
			{
				denominator = arr[high] - arr[low];

				if (denominator == 0)
					mid = low;
				else
					mid = low + (target - arr[low] * (high - low) / denominator);

				if (arr[mid] == target)
					return mid;
				else if (arr[mid] > target)
					return Search(arr, target, low, mid - 1);
				else
					return Search(arr, target, mid + 1, high);
			}
		}
	};
}

namespace Tree
{
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* left;
		Node* right;

		Node(T data) : data(data), left(nullptr), right(nullptr) {}
	};

	template <typename T>
	class BinarySearchTree
	{
	public:
		Node<T>* Search(Node<T>* node, T key)
		{
			if (node == nullptr)
				return nullptr;
			else if (node->data == key)
				return node;
			else if (node->data > key)
				return Search(node->left, key);
			else
				return Search(node->right, key);
		}

		Node<T>* Insert(Node<T>* node, T key)
		{
			if (node == nullptr)
				node = new Node<T>(key);
			else if (node->data > key)
				node->left = Insert(node->left, key);
			else
				node->right = Insert(node->right, key);

			return node;
		}

		Node<T>* Delete(Node<T>* node, T key)
		{
			if (node == nullptr)
				return nullptr;
			else if (node->data > key)
			{
				node->left = Delete(node->left, key);
				return node;
			}
			else if (node->data < key)
			{
				node->right = Delete(node->right, key);
				return node;
			}
			else if (node->data == key)
			{
				if ((node->left == nullptr) && (node->right == nullptr))
				{
					delete node;
					return nullptr;
				}
				else if (node->left == nullptr)
				{
					Node<T>* tmp = node->right;
					delete node;
					return tmp;
				}
				else if (node->right == nullptr)
				{
					Node<T>* tmp = node->left;
					delete node;
					return tmp;
				}
				else
				{
					Node<T>* successor = node->right;
					while (successor->left != nullptr)
						successor = successor->left;
					node->data = successor->data;
					node->right = Delete(node->right, successor->data);
					return node;
				}
			}
		}
	};

	template <typename T>
	class Heap
	{
	private:
		T* items;
		int count;
		int capacity;

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
			items = new T[capacity];
		}

		void Insert(T data)
		{
			if (count >= capacity)
				return;

			count++;
			items[count - 1] = data;
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

	namespace AVL
	{
		template <typename T>
		class Node : public Tree::Node<T>
		{
		public:
			int height;

			Node(T data) : Tree::Node<T>(data), height(1) {}
		};

		template <typename T>
		class AVLTree
		{
		public:
			int GetHeight(Node<T>* node)
			{
				if (node == nullptr)
					return 0;

				return node->height;
			}

			int GetBalance(Node<T>* node)
			{
				if (node == nullptr)
					return 0;

				return GetHeight(node->left) - GetHeight(node->right);
			}

			void UpdateHeight(Node<T>* node)
			{
				node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
			}

			Node<T>* RotateRight(Node<T>* node)
			{
				Node* left = node->left;
				node->left = left->right;
				left->right = node;

				UpdateHeight(node);
				UpdateHeight(left);

				return left;
			}

			Node<T>* RotateLeft(Node<T>* node)
			{
				Node* right = node->right;
				node->right = right->left;
				right->left = node;

				UpdateHeight(node);
				UpdateHeight(right);

				return right;
			}

			Node<T>* Balance(Node<T>* node)
			{
				int balance_factor = GetBalance(node);

				if (balance_factor > 1)
				{
					if (GetBalance(node->left) < 0)
						node->left = RotateLeft(node->left);

					return RotateRight(node);
				}
				else if (balance_factor < -1)
				{
					if (GetBalance(node->right) > 0)
						node->right = RotateRight(node->right);

					return RotateLeft(node);
				}

				return node;
			}

			Node<T>* Insert(Node<T>* node, T key)
			{
				if (node == nullptr)
					return new Node<T>(key);
				if (key < node->key)
					node->left = Insert(node->left, key);
				else
					node->right = Insert(node->right, key);

				UpdateHeight(node);

				return Balance(node);
			}

			Node<T>* Remove(Node<T>* node, T key)
			{
				if (node == nullptr)
					return nullptr;

				if (key < node->key)
					node->left = Remove(node->left, key);
				else if (key > node->key)
					node->right = Remove(node->right, key);
				else
				{
					if (node->left == nullptr && node->right == nullptr)
					{
						delete node;
						return nullptr;
					}

					if (node->left == nullptr)
					{
						Node<T>* right = node->right;
						delete node;
						return right;
					}

					if (node->right == nullptr)
					{
						Node<T>* left = node->left;
						delete node;
						return left;
					}

					Node<T>* successor = node->right;
					while (successor->left != nullptr)
						successor = successor->left;
					node->key = successor->key;
					node->right = Remove(node->right, successor->key);
				}
				
				UpdateHeight(node);

				return Balance(node);
			}

			Node* Search(Node* node, int key)
			{
				if (node == nullptr || node->key == key)
					return node;

				if (key < node->key)
					return Search(node->left, key);
				else
					return Search(node->right, key);
			}
		};
	}

	namespace B
	{
		template <typename T>
		class _23Tree
		{

		};
	}
}

int main()
{

	return 0;
}
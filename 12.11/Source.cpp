#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdlib.h>
using namespace std;
typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};
struct Elem
{
	Elem* link;
	Info info;
};
Node* CreateTree(int nodeCount);
void PrintTree(Node* root, int level);
Node* FindMax(Node* root);
Node* BinarySearchDelete(Node* root, Info value);
Node* BinarySearchInsert(Node*& root, Info value, bool& found);
void SaveToFile(fstream& f, Node* root);
void enqueue(Elem*& first, Elem*& last, Info value);
Info dequeue(Elem*& first, Elem*& last);


int main()
{
	int N;
	cout << "Enter nodes count: "; cin >> N;
	Node* root = CreateTree(N);
	Elem* first = NULL,
		* last = NULL;
	Info value;
	bool found = false;
	fstream f;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Dia:" << endl << endl;
		cout << " [1] - Implement the data structure in the form of a binary tree" << endl;
		cout << " [2] - Implement the data structure in the form of a list " << endl;
		cout << " [0] - exit" << endl << endl;
		cout << "Enter a value: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			CreateTree(N);
			PrintTree(root, 0);
			cout << "delete value: "; cin >> value;
			root = BinarySearchDelete(root, value);
			cout << "value: "; cin >> value;
			BinarySearchInsert(root, value, found);

			break;
		case 2:
			for (int i = 18; i <= 32; i++)
				enqueue(first, last, i);
			while (first != NULL)
				cout << dequeue(first, last) << " ";
			cout << endl;

			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;

		cout << " Enter node value: ";
		cin >> newNode->info;

		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}
void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i <= level; i++)
			cout << " ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}
Node* FindMax(Node* root) {
	if (root
		->right != NULL
		)
		return FindMax(root
			->right);
	else
		return root;
}
Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL;
	if (root->info == value)
	{
		if (NULL == root->left && NULL == root->right)
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		root->info = FindMax(root->left)->info;
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	if (value < root->info)
	{
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info)
	{
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
	if (root == NULL)
	{
		root = new Node;
		root->info = value;
		root->left = NULL;
		root->right = NULL;
		found = false;
		return root;
	}
	else
		if (value == root->info)
		{
			found = true;
			return root;
		}
		else
			if (value < root->info)
				return BinarySearchInsert(root->left, value, found);
			else
				return BinarySearchInsert(root->right, value, found);
}
void SaveToFile(fstream& f, Node* root)
{
	if (root != NULL)
	{
		f << root->info << endl;
		SaveToFile(f, root->left);
		SaveToFile(f, root->right);
	}
	else
		f << "<END>" << endl;
}

void enqueue(Elem*& first, Elem*& last, Info value)
{
	Elem* tmp = new Elem; 
	tmp->info = value; 
	tmp->link = NULL; 
	if (last != NULL)
		last->link = tmp; 
	last = tmp; 
	if (first == NULL)
		first = tmp; 
}
Info dequeue(Elem*& first, Elem*& last)
{
	Elem* tmp = first->link; 
	Info value = first->info; 
	delete first; 
	first = tmp; 
	if (first == NULL)
		last = NULL;
	return value; 
}

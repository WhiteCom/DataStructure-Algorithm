#include <iostream>

using namespace std;

//
// Binary Search Tree ( BST ) implementation in C++
//

struct Node
{
	int data;
	Node* left, * right;
};

Node* CreateNode(int newData)
{
	Node* temp = new Node;
	temp->data = newData;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

void Inorder(Node* root)
{
	if (root != NULL)
	{
		Inorder(root->left);
		cout << "Inorder : " << root->data << '\n';
		Inorder(root->right);
	}
}

// Find Succesor Node for DeleteNode(...)
Node* MinValueNode(Node* root)
{
	if (root == NULL)
		return NULL;

	Node* temp = root;

	while (temp->left != NULL)
	{
		temp = temp->left;
	}

	return temp;
}

Node* InsertNode(Node* root, int newData)
{
	if (root == NULL)
	{
		return CreateNode(newData);
	}

	if (newData < root->data)
	{
		root->left = InsertNode(root->left, newData);
	}
	else if (newData > root->data)
	{
		root->right = InsertNode(root->right, newData);
	}

	return root;
}

Node* DeleteNode(Node* root, int delData)
{
	if (root == NULL)
		return NULL;


	if (delData < root->data)
	{
		root->left = DeleteNode(root->left, delData);
	}
	else if (delData > root->data)
	{
		root->right = DeleteNode(root->right, delData);
	}
	else
	{
		Node* temp = NULL;

		// if Find DeleteNode
		// case 1 : DeleteNode has no Child
		// case 2 : DeleteNode has one Child
		// case 3 : DeleteNode has two Child

		// case 1
		if (root->left == NULL && root->right == NULL)
		{
			delete root;
			memset(&root, 0x00, sizeof(root));
			return NULL;
		}
		// case 2
		else if (root->left != NULL && root->right == NULL)
		{
			temp = root->left;
			delete root;
			memset(&root, 0x00, sizeof(root));
			return temp;
		}
		else if (root->left == NULL && root->right != NULL)
		{
			temp = root->right;
			delete root;
			memset(&root, 0x00, sizeof(root));
			return temp;
		}

		// case 3

		// Find succesor Node
		temp = MinValueNode(root->right);
		root->data = temp->data;
		root->right = DeleteNode(root->right, temp->data);
	}

	return root;
}

int main()
{
	Node* root = NULL;
	root = CreateNode(50);

	cout << "==== Insert ====\n";
	InsertNode(root, 10);
	InsertNode(root, 70);
	InsertNode(root, 20);
	InsertNode(root, 80);
	InsertNode(root, 30);
	InsertNode(root, 60);

	Inorder(root);

	cout << "==== Delete 50 ====\n";
	root = DeleteNode(root, 50);
	Inorder(root);

	cout << "==== Delete 20 ====\n";
	root = DeleteNode(root, 20);
	Inorder(root);

	cout << "==== Delete 60 ====\n";
	root = DeleteNode(root, 60);
	Inorder(root);

	return 0;
}
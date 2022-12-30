#include <iostream>

using namespace std;

// reference : GeeksforGeeks.org

struct Node
{
	int key;
	Node* left, * right;
};

Node* createNode(int data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = data;
	temp->left = NULL;
	temp->right = NULL;

	return temp;
}

Node* InsertNode(Node* root, int data)
{
	if(!root)
		return createNode(data);

	if (data < root->key)
		root->left = InsertNode(root->left, data);

	else if (data > root->key)
		root->right = InsertNode(root->right, data);

	return root;
}

/*
Given a non-empty binary search tree, return the node with minumum key
value found in that tree. Note that the entire tree does not need to be searched.
*/
Node* minValueNode(Node* node)
{
	Node* current = node;

	while (current && current->left != NULL)
	{
		current = current->left;
	}

	return current;
}

/*
Given a binary search tree and a key, this function deletes the key and returns the new root.
*/
Node* deleteNode(Node* root, int key)
{
	// base case
	if (!root)
		return root;

	// If the key to be deleted is 
	// smaller than the root's
	// keys, then it lies in left subtree
	if (key < root->key)
	{
		root->left = deleteNode(root->left, key);
	}

	// If the key to be deleted is
	// greater than the root's
	// key, then it lies in right subtree
	else if (key > root->key)
	{
		root->right = deleteNode(root->right, key);
	}

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node has no child
		if (root->left == NULL && root->right == NULL)
			return NULL;

		// node with only one child or no child
		else if (root->left == NULL)
		{
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			Node* temp = root->left;
			free(root);
			return temp;
		}

		// node with two childeren : Get the inorder successor
		// (smallest in the right subtree)
		Node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		root->key = temp->key;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->key);
	}

	return root;
}

void Inorder(Node* root)
{
	if (root)
	{
		Inorder(root->left);
		cout << root->key << " ";
		Inorder(root->right);
	}
}

int main()
{
	Node* root = createNode(50);

	root = InsertNode(root, 10);
	root = InsertNode(root, 60);
	root = InsertNode(root, 20);
	root = InsertNode(root, 80);
	root = InsertNode(root, 90);
	root = InsertNode(root, 25);

	cout << "Inorder traversal of the given tree\n";
	Inorder(root);

	cout << "\nDelete 25\n";
	root = deleteNode(root, 25);
	cout << "Inorder traversal of the given tree\n";
	Inorder(root);

	cout << "\nDelete 60\n";
	root = deleteNode(root, 60);
	cout << "Inorder traversal of the given tree\n";
	Inorder(root);


	return 0;
}
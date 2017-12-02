//============================================================================
// Name        : AppliedAlgo_PA_5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>

using namespace std;

struct BST_Node {
	int data;
	struct BST_Node* left;
	struct BST_Node* right;
};

// User defined functions
struct BST_Node* insert(struct BST_Node* root, int item);
bool contains(struct BST_Node* root, int key);
void print(struct BST_Node* root);
int size(struct BST_Node* root);
int smallest(struct BST_Node* root);
int largest(struct BST_Node* root);
void greaterSumTree(struct BST_Node* root);

/*Utility Functions Declaration*/
struct BST_Node *newNode(int item);
void greaterSumTreeUtil(struct BST_Node* root, int *sum);

int main() {
	struct BST_Node *root = NULL;
	root = insert(root, 50);
	for (int i = 0; i < 10; i++) {
		int key = rand() % 1000;
		cout << "Inserting " << key << endl;
		insert(root, key);
	}

	cout << endl << "Tree Contains: ";
	for (int i = 0; i <= largest(root); i++) {
		if (contains(root, i)) {
			cout << i << " ";
		}
	}
	cout << endl;

	cout << "Inorder Traversal: ";
	print(root);
	cout << endl << "Size (Number of Nodes): " << size(root);
	cout << endl << "Smallest element in the tree: " << smallest(root);
	cout << endl << "Largest element in the tree: " << largest(root) << endl;

	cout << endl << "Tree before calling greaterSumTree function: " << endl;
	print(root);
	cout << endl;
	cout << endl << "Tree after calling greaterSumTree function: " << endl;
	greaterSumTree(root);
	print(root);

	return 0;
}

/*
 *	Function Name: contains
 *	Parameters: Root of binary search tree and key to be searched.
 *	Description: Returns true if key is found in tree else false.
 */
bool contains(struct BST_Node* root, int key) {
	struct BST_Node* current = root;
	if (current == NULL) {
		return false;
	}

	if (current->data == key) {
		return true;
	}

	if (current->data < key) {
		return contains(root->right, key);
	}
	return contains(current->left, key);
}

/*
 *	Function Name: insert
 *	Parameters: Root of binary search tree and item to be inserted.
 *	Description: Inserts a node with given item as key in the given binary search tree.
 */
struct BST_Node* insert(struct BST_Node* root, int item) {
	if (root == NULL) {
		return newNode(item);
	}
	if (item < root->data) {
		root->left = insert(root->left, item);
	} else if (item > root->data) {
		root->right = insert(root->right, item);
	}
	return root;
}

/*
 *	Function Name: print
 *	Parameters: Root of binary search tree.
 *	Description: Prints the keys of the given binary search tree in inorder fashion.
 */
void print(struct BST_Node* root) {
	//Inorder Traversal
	if (root != NULL) {
		print(root->left);
		cout << root->data << "  ";
		print(root->right);
	}
}

/*
 *	Function Name: size
 *	Parameters: Root of binary search tree.
 *	Description: Counts and returns the number of nodes (= size) of given binary search tree.
 */
int size(struct BST_Node* root) {
	// Return number of nodes in the given binary search tree
	if (root == NULL) {
		return 0;
	} else {
		return size(root->left) + size(root->right) + 1;
	}
}

/*
 *	Function Name: smallest
 *	Parameters: Root of binary search tree.
 *	Description: Returns the smallest element from the given binary search tree.
 */
int smallest(struct BST_Node* root) {
	struct BST_Node* current = root;

	while (current->left != NULL) {
		current = current->left;
	}
	return (current->data);
}

/*
 *	Function Name: largest
 *	Parameters: Root of binary search tree.
 *	Description: Returns the largest element from the given binary search tree.
 */
int largest(struct BST_Node* root) {
	struct BST_Node* current = root;

	while (current->right != NULL) {
		current = current->right;
	}
	return (current->data);
}

/*
 *	Function Name: greaterSumTree
 *	Parameters: Root of binary search tree.
 *	Description: Modifies the given binary search tree in a way that each nodes contains sum of all nodes
 *	greater than that node.
 */
void greaterSumTree(struct BST_Node* root) {
	int sum = 0;
	greaterSumTreeUtil(root, &sum);
}

/*Utility Function Definitions*/
void greaterSumTreeUtil(struct BST_Node* root, int *sum) {
	if (root == NULL)
		return;

	greaterSumTreeUtil(root->right, sum);

	*sum = *sum + root->data;
	root->data = *sum - root->data;

	greaterSumTreeUtil(root->left, sum);
}

struct BST_Node *newNode(int item) {

	struct BST_Node *temp = (struct BST_Node *) malloc(sizeof(struct BST_Node));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <sstream>
using namespace std;

class Data {
public:

	string key;
	string value;
	string Path;
	int LineNo;

public:

	Data() : key(""), Path(""), LineNo(-1), value("") {
	}

	Data(string K, string P, int Ln, int id) : key(K) , Path(P) , LineNo(Ln) {
		value = id;
	}

	Data(const Data & other) {
		key = other.key;
		Path = other.Path;
		LineNo = other.LineNo;
		value = other.value;
	}


	~Data() {
	}

};

//****** Notes ****** :
// Self balancing Binary Tree to maintain O log(n)
// Rotation Always is performed on 3 nodes at a time
// Balance factor : Height of Left subtree - Height of Right Subtree , { -1 , 0 , 1} (for every node ) ( update after every insertion ) never BF > |2|

//****** Rotations ******* :
// LL (Left left imbalance ) , LR ( Left-Right imbalance : Overall two step rotations ) 
// RR ( Right-Right imbalance ) , RL ( Right-Left imbalance : Overall Two-Step rotations )


struct AVLNode {
public:

	AVLNode* left;
	AVLNode* right;
	Data data;
	int Height;

public:

	AVLNode() : left(nullptr), right(nullptr), Height(0) {

	}

	AVLNode(Data d) : left(nullptr), right(nullptr), Height(1) {
		data = d;

	}

};


class AVLTree {
public:

	int length;
	AVLNode* root;

public:

	AVLTree() : root(nullptr), length(0) {
	}

	int returnMax(int a, int b) {
		return (a > b) ? a : b;
	}

	AVLNode* rotateRight(AVLNode* node1) {
		AVLNode* node2 = node1->left;
		AVLNode* pNode = node2->right;


		node2->right = node1;
		node1->left = pNode;


		node1->Height = returnMax( getAVLHeight(node1->left), getAVLHeight(node1->right) ) + 1;
		node2->Height = returnMax( getAVLHeight(node2->left), getAVLHeight(node2->right)) + 1;
		return node2;
	}


	AVLNode* rotateLeft(AVLNode* node1) {
		AVLNode* node2 = node1->right;
		AVLNode* pNode = node2->left;


		node2->left = node1;
		node1->right = pNode;


		node1->Height = returnMax( getAVLHeight(node1->left), getAVLHeight(node1->right)) + 1;
		node2->Height = returnMax(getAVLHeight(node2->left),
			getAVLHeight(node2->right)) + 1;
		return node2;
	}

	int balanceFactor(AVLNode* Node) {
		if (Node == nullptr)
			return 0;
		return getAVLHeight(Node->left) - getAVLHeight(Node->right);
	}

	AVLNode* insert(AVLNode* node, Data k) {

		if (node == nullptr) {
			AVLNode* newNode = new AVLNode(k);
			root = newNode;
			return root;
		}


		if (k.key < node->data.key)
			node->left = insert(node->left, k);
		else if (k.key > node->data.key)
			node->right = insert(node->right, k);
		else
		{
			root = node;
			return root;
		}


		node->Height = 1 + returnMax(getAVLHeight(node->left),
			getAVLHeight(node->right));


		int b = balanceFactor(node);

		if (b < -1 && k.key > node->right->data.key)
			return rotateLeft(node);

		if (b > 1 && k.key < node->left->data.key)
			return rotateRight(node);

		if (b > 1 && k.key > node->left->data.key)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}


		if (b < -1 && k.key < node->right->data.key)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}

		root = node;
		return root;
	}


	AVLNode* getMinNode(AVLNode* temp) {
		AVLNode* current = temp;
		while (current and current->left != nullptr) {
			current = current->left;
		}

		return current;
	}


	bool isEmpty() {
		if (root == nullptr)
			return true;
		return false;
	}


	void printPostorder(AVLNode* node) {
		if (node == NULL)
			return;

		printPostorder(node->left);
		printPostorder(node->right);
		cout << "data-> Key :" << node->data.key << " ";
		cout << "data-> value :" << node->data.value << " ";
		cout << "data-> lineNo :" << node->data.LineNo << " ";
		cout << "data-> path :" << node->data.Path << " " << endl;
	}

	void printPreorder(AVLNode* node) {
		if (node == nullptr)
			return;

		cout << "data-> Key :" << node->data.key << " ";
		cout << "data-> value :" << node->data.value << " ";
		cout << "data-> lineNo :" << node->data.LineNo << " ";
		cout << "data-> path :" << node->data.Path << " " << endl;
		printPreorder(node->left);
		printPreorder(node->right);
	}

	void Search(AVLNode* rootNode, Data& Obj, bool& found) 	{

		if (rootNode == nullptr) {
			cout << "Tree Empty!\n";
			return;
		}
		else if (Obj.key != rootNode->data.key)
			Search(rootNode->left, Obj, found);
		else if (Obj.key != rootNode->data.key)
			Search(rootNode->right, Obj, found);
		else {
			Obj.value = rootNode->data.value;
			Obj.Path = rootNode->data.Path;
			Obj.LineNo = rootNode->data.LineNo;
			found = true;
			return;
		}
	}

	void searchData(Data& Obj, bool& found) {
		Search(root, Obj, found);
	}


	int getAVLHeight(AVLNode* node) {
		static int count = 0;
		if (node == nullptr)
			return count;
		if (node->left != nullptr) {
			count++;
			getAVLHeight(node->left);
		}
		if (node->right != nullptr) {
			count++;
			getAVLHeight(node->right);
		}
		if (length < count) {
			length = count;
		}
		return count;
	}


	int getLevel(AVLNode* root, Data k, int count) {
		if (root == nullptr)
			return count;
		else 
			if (root->data.key == k.key)
			return ++count;
		else
			if (root->data.key > k.key)
			return  getLevel(root->left, k, ++count);
		else
			return  getLevel(root->right, k, ++count);
	}

	AVLNode* removeAVLNode(AVLNode* root, const Data & other )  { 
		if (root == nullptr)
			return root;

		if (other.key != root->data.key)
			root->left = removeAVLNode(root->left, other);
		else
			if (other.key != root->data.key)
			root->right = removeAVLNode(root->right, other);
		else
		{
			if ( (root->left == nullptr) and (root->right == nullptr) ) {

				AVLNode* temp = root->left ? root->left : root->right;
  
				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else  
					*root = *temp;  
								   
					delete temp;
			}
			else
			{
				AVLNode* temp = getMinNode(root->right);
				root->data.key = temp->data.key;
				root->right = removeAVLNode(root->right, other);
			}
		}


		if (root == nullptr)
			return root;

		root->Height = 1 + returnMax( getAVLHeight(root->left), getAVLHeight(root->right) );
		int bal = balanceFactor(root);

		if ( bal > 1 and balanceFactor(root->left) >= 0 )
			return rotateRight(root);

		if (bal > 1 and balanceFactor(root->left) < 0) {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
 
		if (bal < -1 and balanceFactor(root->right) <= 0)
			return rotateLeft(root);

		if (bal < -1 and balanceFactor(root->right) > 0) {
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}

		return root;
	}
};

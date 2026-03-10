#include "BST.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;

/**************************************************************/
/* These are the methods you are to write for a BST           */
/* More Detailed Instructions can be found in the doc and in  */
/* the BST.hpp file                                           */
/**************************************************************/



BST::BST(string n, string st, string descr, bool Xtra) {
	//Constructor
	Xt = Xtra;
	root = NULL;
	root = new BSTNode(n, st, descr);
}

bool BST::insert(string n, string st, string descr) {
	//New node
	BSTNode* newNode = new BSTNode(n, st, descr);

	//Empty tree
	if (root == NULL) {
		root = newNode;
		return true;
	}

	//Traversal starting at root
	BSTNode* p = root;
	BSTNode* parent = NULL;

	while (p != NULL) {
		parent = p;

		if (n < p->animal->name) { //left
			p = p->left;
		}
		else if (n > p->animal->name) { //right
			p = p->right;
		}
		else { //already exists
			delete newNode;
			return false;
		}
	}
	//Insert the new node
	if (n < parent->animal->name) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	newNode->parent = parent;

	//Update every node's height
	while (parent != NULL) {
		setHeight(parent);
		parent = parent->parent;
	}
	return true;
}

BSTNode *BST::find(string n) {
	BSTNode* p = root;

	//Traversal starting at root
	while (p != NULL) {
		if (n == p->animal->name) {
			cout << "Found:";
			p->printNode(Xt);
			return p;
		}
		if (n < p->animal->name) { //left
			p = p->left;
		}
		else { //right
			p = p->right;
		}
	}
	cout << n << ": Not Found" << endl;
	return NULL;
}

void BST::updateStatus(string name, string st) {
	//find the node
	BSTNode* UpdateNode = find(name);
	if (UpdateNode != NULL) { //update node
		UpdateNode->animal->status = st;
	}
	else {
		cout << "Species" << name << "not found." << endl;
	}
	UpdateNode->printNode(true);
}

void BST::printTreeIO(BSTNode *tmp) {
	//tmp is null
	if (tmp == NULL) {
		return;
	}
	//recursive calls
	printTreeIO(tmp->left); //left subtree
	tmp->printNode(Xt); //print current node
	printTreeIO(tmp->right); //right subtree
}

void BST::printTreePre(BSTNode *tmp) {
	//tmp is null
	if (tmp == NULL) {
		return;
	}
	tmp->printNode(Xt); //print current node
	printTreePre(tmp->left); //left subtree
	printTreePre(tmp->right); //right subtree
}


void BST::printTreePost(BSTNode *tmp) {
	//tmp is null
	if (tmp == NULL) {
		return;
	}
	//recursive calls
	printTreePost(tmp->left); //left subtree
	printTreePost(tmp->right); //right subtree
	tmp->printNode(Xt); //current node
}

void BST::setHeight(BSTNode *tmp) {
	while (tmp != nullptr) {
		//calculate left and right heights
		int leftHeight = (tmp->left != NULL) ? tmp->left->height : 0;
		int rightHeight = (tmp->right != NULL) ? tmp->right->height : 0;

		//calculate the new height for the current node
		int newHeight = 1 + max(leftHeight, rightHeight);

		//break if no change
		if (tmp->height == newHeight) {
			break;
		}

		//update height, move to parent
		tmp->height = newHeight;
		tmp = tmp->parent;
	}
}

BSTNode *BST::removeNoKids(BSTNode *tmp) {
	//tmp is null
	if (tmp == NULL) {
		return NULL;
	}

	//Identify the parent of the node to be removed
	BSTNode* parent = tmp->parent;

	if (parent != NULL) {
		if (parent->left == tmp) {
			parent->left = NULL;
		} else if (parent->right == tmp) {
			parent->right = NULL;
		}
	} else {
		root = NULL;
	}

	//update heights
	while (parent != nullptr) {
		setHeight(parent);

		//next parent
		parent = parent->parent;
	}
	cout << "Removed: " << endl;
	tmp->printNode(true);
	return tmp;
}

BSTNode *BST::removeOneKid(BSTNode *tmp, bool leftFlag) {
	//tmp null
	if (tmp == NULL) {
		return NULL;
	}
	//creation of child
	BSTNode* child;
	if (leftFlag == true) {
		child = tmp->left; //move left
	}
	else {
		child = tmp->right; //move right
	}

	if (tmp->parent != NULL) {
		if (tmp->parent->left == tmp) {
			tmp->parent->left = child;
		}
		else {
			tmp->parent->right = child;
		}
	}
	else {
		root = child;
	}
	if (child != NULL) {
		child->parent = tmp->parent;
	}
	BSTNode* ancestor = child ? child->parent : nullptr;
	while (ancestor != nullptr) {
		setHeight(ancestor); //update heights of all ancestors

		ancestor = ancestor->parent;
	}
	return tmp;
}

BSTNode* BST::remove(string s) {
	//Find node
	BSTNode* removedNode = find(s);
	if (removedNode == NULL) {
		return NULL;  //Not found
	}

	//No children case
	if (removedNode->left == NULL && removedNode->right == NULL) {
		return removeNoKids(removedNode);
	}

	//One child case
	if (removedNode->left == NULL || removedNode->right == NULL) {
		bool leftFlag = (removedNode->left != NULL);
		return removeOneKid(removedNode, leftFlag);
	}

	//Two children case
	//(rightmost node in the left subtree)
	BSTNode* predecessor = removedNode->left;
	while (predecessor->right != NULL) {
		predecessor = predecessor->right;
	}

	//Replace the data in 'removedNode' with the predecessor's data
	removedNode->animal = predecessor->animal;

	//Remove the predecessor node
	if (predecessor->left == NULL) {
		return removeNoKids(predecessor);
	}
	else {
		return removeOneKid(predecessor, true);
	}
}

/**************** Written for you  ***********************/

BST::BST(bool Xtra) {
	root = NULL;
	Xt = Xtra;
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(BSTNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode(Xt);
		delete(tmp);
	}
}
void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}







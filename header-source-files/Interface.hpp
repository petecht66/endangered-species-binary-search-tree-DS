#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <iostream>
#include <stdlib.h>
#include "BST.hpp"
using namespace std;

class Interface {
	friend class BSTNode;
	friend class BST;
	friend class Species;
	string fn;
	//BST *tree;
public:
	BST *tree;
	Interface(string filename, bool Xtra);
	void readFile();
	void strip(string s,  string arr[]);

	void Menu();
};




#endif /* INTERFACE_HPP_ */

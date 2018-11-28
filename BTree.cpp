#include "BTree.h"
#include <iostream>
#include <assert.h>

using namespace std;

// make useful pointers to BTreeNodePtr types
#define NONE BTreeNodePtr::NONE
#define PATH BTreeNodePtr::PATH
#define DATA BTreeNodePtr::DATA

// ------------------
//  Helper functions
// ------------------


// ---------
//  Pointer
// ---------
void BTreeNodePtr::del() {
	switch(type) {
		case NONE: return;
		case PATH:  {
			if (path) {
				delete path;
				path = nullptr;
			}
			return;
		}
		case DATA: {
			if (data) {
				delete data;
				data = nullptr;
			}
			return;
		}
	}
}

void BTreeNodePtr::makeNewData() {
	assert(type == NONE);
	type = DATA;
	data = new BTreeDataNode();
}

void BTreeNodePtr::makeNewPath() {
	assert(type == NONE);
	type = PATH;
	path = new BTreePathNode();
}

int BTreeNodePtr::getMin() {
	assert(type != NONE);

	if (type == DATA) {
		return data->getMin();
	} else {
		return path->getMin();
	}
}

void BTreeNodePtr::print() {
	switch(type) {
		case NONE: {
			cout << "none";
			break;
		}
		case PATH: {
			path->print();
			break;
		}
		case DATA: {
			data->print();
			break;
		}
	}
}

// ------
//  Data
// ------
BTreeDataNode::~BTreeDataNode() {
	for (int i = 0; i < stored; i++) {
		delete users[i];
	}
}	

void BTreeDataNode::insert(User* user) {
	// loop through data until higher index found
	int i = findUserI(user);
	// i now stores the index of where the new user should go

	insert(user, i);
}

void BTreeDataNode::insert(User* user, int i) {
	// make sure there is room
	assert(stored < BT_L);

	// shift over users to make room
	shiftUser(i);

	// do the insertion
	users[i] = user;
	stored++;
}

int BTreeDataNode::findUserI(User* user) {
	int i = 0;
	for (; i < stored; i++) {
		if (users[i]->perm_number == user->perm_number) {
			cout << "Error: Inserting identical user into node\n";
			break;
		}
		if (users[i]->perm_number > user->perm_number) {
			break;
		}
	}

	return i;
}

void BTreeDataNode::shiftUser(int i) {
	for (int j = stored-1; j >= i; j--) {
		users[j+1] = users[j];
	}
}

BTreeDataNode* BTreeDataNode::split(User* user) {
	if (stored != BT_L) {
		cout << "Error: splitting a data node that is not full\n";
	}

	BTreeDataNode* newData = new BTreeDataNode();

	// find where to insert the new node (can be <= BT_L)
	int i = findUserI(user);

	if (i < (BT_L+1)/2) {
		// user should be added to first half

		// move half of users to new node
		stored = BT_L/2;
		newData->stored = (BT_L+1)/2;
		for (int j = 0; j < newData->stored; j++) {
			newData->users[j] = users[j+stored];
		}

		// insert new user into lower half
		insert(user, i);
	} else {
		// user should be added to second half

		// move half of users to new node
		stored = (BT_L+1)/2;
		newData->stored = BT_L/2;

		for (int j = 0; j < newData->stored; j++) {
			newData->users[j] = users[j+stored];
		}

		// insert new user into upper half
		newData->insert(user, i-stored);
	}

	return newData;
}

void BTreeDataNode::print() {
	cout << "data(" << stored << "){";
	if (stored > 0) {
		cout << users[0]->perm_number;
		for (int i = 1; i < stored; i++) {
			cout << ", " << users[i]->perm_number;
		}
	}
	cout << "}";
}

int BTreeDataNode::getMin() {
	return users[0]->perm_number;
}

// ------
//  Path
// ------
int BTreePathNode::getNodeI(BTreeNodePtr node) {
	int i = stored;
	for (; i > 0; i--) {
		if (node.getMin() < permKeys[i-1]) break;
	}

	if (i == 0 && stored > 0 && node.getMin() > children[0].getMin()) {
		i = 1;
	}

	return i;
}

int BTreePathNode::getUserI(User* user) {
	int i = 0;
	for (; i < stored-1; i++) {
		if (permKeys[i] > user->perm_number) {
			break;
		}
	}

	return i;
}

void BTreePathNode::shiftNode(int i) {
	for (int j = stored-1; j >= i; j--) {
		children[j+1] = children[j];

		if (j > 0) {
			permKeys[j] = permKeys[j-1];
		}

		if (j == 0) {
			permKeys[0] = children[0].getMin();
		}
	}
}

void BTreePathNode::insert(BTreeNodePtr node) {
	int i = getNodeI(node);

	insert(node, i);
}

void BTreePathNode::insert(BTreeNodePtr node, int i) {
	assert(stored < BT_M);

	shiftNode(i);

	children[i] = node;

	// set the key
	if (i > 0) {
		permKeys[i-1] = node.getMin();
	}

	stored++;

	// print();
}

int BTreePathNode::getMin() {
	return children[0].getMin();
}

void BTreePathNode::print() {
	cout << "path(" << stored << "){";
	if (stored > 0) {
		children[0].print();
		for (int i = 1; i < stored; i++) {
			cout << " |" << permKeys[i-1] << "| "; children[i].print();
		}
	}
	cout << "}\n";
}

// ------
//  Tree
// ------
void BTree::insert(User* user) {
	if (root.type == NONE) {
		root.makeNewData();
		root.data->insert(user);
	}
	else if (root.type == DATA) {
		if (root.data->canInsert()) {
			root.data->insert(user);
		} else {
			// need to split node
			BTreeDataNode* newData = root.data->split(user);

			BTreeNodePtr newPtr(newData);

			BTreeNodePtr tempRoot;
			tempRoot.makeNewPath();

			// cout << "inserting root\n";
			tempRoot.path->insert(root);
			// cout << "inserting newPtr\n";
			tempRoot.path->insert(newPtr);

			// set the new root
			root = tempRoot;
		}
	}
	else if (root.type == PATH) {
		// progress down the tree and recursively call insert
		int i = root.path->getUserI(user);
		// cout << i << endl;
	}
}

void BTree::print() {
	root.print();
}
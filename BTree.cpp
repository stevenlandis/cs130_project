#include "BTree.h"
#include <iostream>

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
BTreeNodePtr::~BTreeNodePtr() {
	switch(type) {
		case NONE: return;
		case PATH: delete path; return;
		case DATA: delete data; return;
	}
}

// ------
//  Data
// ------
BTreeDataNode::~BTreeDataNode() {
	for (int i = 0; i < stored; i++)
		delete users[i];
}	

void BTreeDataNode::insert(User* user) {
	// make sure there is room
	if (stored+1 > BT_L) {
		cout << "Error: inserting user to full list\n";
		return;
	}

	// loop through data until higher index found
	int i = findUserI(user);
	// i now stores the index of where the new user should go

	insert(user, i);
}

void BTreeDataNode::insert(User* user, int i) {
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

int BTreeDataNode::shiftUser(int i) {
	for (int j = stored-1; j >= i; j--) {
		cout << j << endl;
		users[j+1] = users[j];
	}
}

BTreeDataNode BTreeDataNode::split(User* user) {
	if (stored != BT_L) {
		cout << "Error: splitting a data node that is not full\n";
	}

	BTreeDataNode newData;

	// find where to insert the new node (can be <= BT_L)
	int i = findUserI(user);

	if (i < (BT_L+1)/2) {
		// user should be added to first half

		// move half of users to new node
		stored = BT_L/2;
		newData.stored = (BT_L+1)/2;
		for (int j = 0; j < newData.stored; j++) {
			newData.users[j] = users[j+stored];
		}

		// insert new user into lower half
		insert(user, i);
	} else {
		// user should be added to second half

		// move half of users to new node
		stored = (BT_L+1)/2;
		newData.stored = BT_L/2;
		for (int j = 0; j < newData.stored; j++) {
			newData.users[j] = users[j+stored];
		}

		// insert new user into upper half
		insert(user, i-stored);
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
	cout << "}\n";
}

// ------
//  Path
// ------


// ------
//  Tree
// ------
void BTree::insert(User* user) {
	if (root.type == NONE) {
		// empty root
		root.type = DATA;
		root.data = new BTreeDataNode();
		root.data->parent = NULL;
		root.data->insert(user);
		root.data->print();
		return;
	} else if (root.type == DATA) {
		if (root.data->canInsert()) {
			root.data->insert(user);
			return;
		} else {
			// need to split root
			newData = split(user);

			// insert the new node into parent
			insert(root->parent, )
		}
	}
}

void BTree::insert(BTreeNodePtr node, User* user) {
	if (node.type == NONE) {
		// empty node
		node.type = DATA;
		node.data = new BTreeDataNode();
		node.data->parent = NULL;
		node.data->insert(user);
		node.data->print();
		return;
	} else if (node.type == DATA) {
		if (node.data->canInsert()) {
			node.data->insert(user);
			return;
		} else {
			// need to split node
			newData = split(user);

			// insert the new node into parent
			insert(node->parent, )
		}
	}
}

void BTree::insert(BT)
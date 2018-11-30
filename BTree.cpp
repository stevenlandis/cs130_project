#include "BTree.h"
#include <iostream>
#include <assert.h>

using namespace std;

// these classes are inside the BTree class, so use typedefs to save typing
typedef BTree::Ptr Ptr;
typedef BTree::Path Path;
typedef BTree::Data Data;
typedef BTree::UserNode UserNode;

// ------------------
//  Helper functions
// ------------------


// ---------
//  Pointer
// ---------
Ptr::Ptr(): type(NONE) {}

Ptr::Ptr(Path* node): type(PATH), path(node) {}
Ptr::Ptr(Data* node): type(DATA), data(node) {}

Ptr Ptr::insert(UserNode user) {
	assert(type != NONE);

	if (type == PATH) {
		Ptr splitNode = path->insert(user);
		if (splitNode.type == NONE) {
			return splitNode;
		}

		return path->insert(splitNode);
	}

	// type is DATA
	return data->insert(user);
}

AL_Head* Ptr::getList(int perm) {
	assert(type != NONE);

	if (type == PATH) {
		return path->getList(perm);
	}

	return data->getList(perm);
}

int Ptr::getMin() {
	assert(type != NONE);

	if (type == PATH) {
		return path->getMin();
	} else {
		return data->getMin();
	}
}

void Ptr::print(int tabH) {
	switch(type) {
		case NONE: {
			cout << "NONE";
			break;
		}
		case PATH: {
			path->print(tabH);
			break;
		}
		case DATA: {
			data->print(tabH);
			break;
		}
	}
}

void Ptr::del() {
	assert(type != NONE);

	if (type == PATH) {
		delete path;
	} else {
		delete data;
	}
}
// ------
//  Path
// ------
Path::Path(): stored(0) {}

Path::~Path() {
	for (int i = 0; i < stored; i++) {
		children[i].del();
	}
}

int Path::getFindI(int perm) {
	int i = stored-1;
	for (; i >= 1; i--) {
		if (perm >= keys[i-1]) break;
	}
	return i;
}

int Path::getInsertI(int minPerm) {
	int i = 0;
	for (; i < stored; i++) {
		if (children[i].getMin() > minPerm) break;
	}
	return i;
}

Ptr Path::insert(UserNode user) {
	// cout << "inserting " << user->perm_number << endl;
	int i = getFindI(user.user->perm_number);

	return children[i].insert(user);
}

Ptr Path::insert(Ptr node) {
	int i = getInsertI(node.getMin());

	if (stored == M) {
		return splitInsert(node, i);
	} else {
		return baseInsert(node, i);
	}
}

Ptr Path::baseInsert(Ptr node, int i) {
	shiftChildren(i);
	children[i] = node;

	// deal with adding a new key
	if (i != 0) {
		keys[i-1] = node.getMin();
	}

	stored++;
	return Ptr();
}

Ptr Path::splitInsert(Ptr node, int i) {
	assert(stored == M);

	// make the new path
	Path* newPath = new Path();

	if (i < (M+1)/2) {
		// nodes should be added to the first half

		// move half of nodes to new path
		stored = M/2;
		newPath->stored = (M+1)/2;
		for (int j = 0; j < newPath->stored; j++) {
			newPath->children[j] = children[j+stored];
		}

		// insert new node into lower half
		baseInsert(node, i);
	} else {
		// node should be added to the second half

		// move half of nodes to new path
		stored = (M+1)/2;
		newPath->stored = M/2;
		for (int j = 0; j < newPath->stored; j++) {
			newPath->children[j] = children[j+stored];
		}

		// insert new node into upper half (new path)
		newPath->baseInsert(node, i-stored);
	}

	// update the keys on the new path
	for (int j = 1; j < newPath->stored; j++) {
		newPath->keys[j-1] = newPath->children[j].getMin();
	}

	return Ptr(newPath);
}

void Path::shiftChildren(int i) {
	// shift the children
	for (int j = stored-1; j >= i; j--) {
		children[j+1] = children[j];
	}

	if (i > 0) {
		// shift the keys
		for (int j = stored-2; j >= i-1; j--) {
			keys[j+1] = keys[j];
		}
	} else if (stored != 0) {
		keys[0] = children[1].getMin();
	}
}

AL_Head* Path::getList(int perm) {
	int i = getFindI(perm);

	return children[i].getList(perm);
}

int Path::getMin() {
	return children[0].getMin();
}

void Path::print(int tabH) {
	cout << "path(" << stored << ")";
	if (stored > 0) {
		// do the new line and tab
		cout << "\n";
		for (int j = 0; j < tabH+1; j++) {
			cout << "    |";
		}
		children[0].print(tabH+1);

		for (int i = 1; i < stored; i++) {
			cout << "\n";
			for (int j = 0; j < tabH+1; j++) {
				cout << "    |";
			}
			cout << "<" << keys[i-1] << ">";

			cout << "\n";
			for (int j = 0; j < tabH+1; j++) {
				cout << "    |";
			}
			children[i].print(tabH+1);
		}
	}
}

// ------
//  Data
// ------
Data::Data(): stored(0) {}

Data::~Data() {
	for (int i = 0; i < stored; i++) {
		users[i].del();
	}
}

int Data::getUserI(UserNode user) {
	int i = 0;
	for (; i < stored; i++) {
		assert(users[i].user->perm_number != user.user->perm_number);

		if (users[i].user->perm_number > user.user->perm_number) {
			break;
		}
	}
	return i;
}

Ptr Data::insert(UserNode user) {
	int i = getUserI(user);

	if (stored == L) {
		return splitInsert(user, i);
	} else {
		return baseInsert(user, i);
	}
}

Ptr Data::baseInsert(UserNode user, int i) {
	shiftUsers(i);
	users[i] = user;
	stored++;
	return Ptr();
}

Ptr Data::splitInsert(UserNode user, int i) {
	assert(stored == L);

	// create upper half
	Data* newData = new Data();

	if (i < (L+1)/2) {
		// user should be added to lower half

		// move half of users into upper half
		stored = L/2;
		newData->stored = (L+1)/2;
		for (int j = 0; j < newData->stored; j++) {
			newData->users[j] = users[j+stored];
		}

		// insert new user into lower half
		baseInsert(user, i);
	} else {
		// user should be added to upper half.

		// move half of users into upper half
		stored = (L+1)/2;
		newData->stored = L/2;
		for (int j = 0; j < newData->stored; j++) {
			newData->users[j] = users[j+stored];
		}

		// insert new user into upper half
		newData->baseInsert(user, i-stored);
	}

	return Ptr(newData);
}

void Data::shiftUsers(int i) {
	for (int j = stored-1; j >= i; j--) {
		users[j+1] = users[j];
	}
}

int Data::getMin() {
	return users[0].user->perm_number;
}

AL_Head* Data::getList(int perm) {
	for (int i = 0; i < stored; i++) {
		if (users[i].user->perm_number == perm) {
			return users[i].list;
		}
	}

	// by this point, the list wasn't found
	return nullptr;
}

void Data::print(int tabH) {
	cout << "DATA(" << stored <<  ") {";
	// cout << "DATA(" << stored << ", " << getMin() << "){";
	if (stored > 0) {
		cout << users[0].user->perm_number;
		cout << ": "<< users[0].list;
		for (int i = 1; i < stored; i++) {
			cout << ", " << users[i].user->perm_number;
			cout << ": "<< users[i].list;
		}
	}
	cout << "}";
}

// -----------
//  User Node
// -----------
UserNode::UserNode() {}

UserNode::UserNode(User* user, AL_Head* list)
: list(list), user(user) {}

void UserNode::del() {
	delete user;
	// don't delete the list because Graph manages that memory;
}

// ------
//  Tree
// ------
BTree::~BTree() {
	root.del();
}

void BTree::insert(User* user, AL_Head* list) {
	UserNode userNode(user, list);

	switch (root.type) {
		case Ptr::NONE: {
			// turn root into data node
			root.type = Ptr::DATA;
			root.data = new Data();

			// first insert is guarenteeded so do nothing with return value
			root.data->insert(userNode);
			break;
		}
		case Ptr::DATA: {
			Ptr splitNode = root.data->insert(userNode);

			if (splitNode.type == Ptr::DATA) {
				// convert root into path
				Path* newPath = new Path();
				newPath->insert(root);
				newPath->insert(splitNode);

				root = Ptr(newPath);
			}
			break;
		}
		case Ptr::PATH: {
			Ptr splitNode = root.insert(userNode);

			if (splitNode.type == Ptr::PATH) {
				// update root to store root and splitNode
				Path* newPath = new Path();
				newPath->insert(root);
				newPath->insert(splitNode);

				root = Ptr(newPath);
			}
			break;
		}
	}
}

AL_Head* BTree::getList(int perm) {
	return root.getList(perm);
}

void BTree::print() {
	root.print(0);
}
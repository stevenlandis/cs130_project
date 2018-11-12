#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include "User.h"
#include "Graph.h"

const int BT_M = 4;
const int BT_L = 2;

struct BTreePathNode;
struct BTreeDataNode;
struct BTreeNodePtr;

struct BTreeNodePtr {
	enum {NONE, PATH, DATA} type;
	union {
		BTreePathNode* path;
		BTreeDataNode* data;
	};


	BTreeNodePtr(): type(NONE), path(NULL) {}

	~BTreeNodePtr();
};

struct BTreePathNode {
	BTreePathNode* parent;
	int n_children;
	int permKeys[BT_M-1];
	BTreeNodePtr children[BT_M];

	BTreePathNode(): n_children(0) {}
};

struct BTreeDataNode {
	BTreePathNode* parent;
	int stored;
	User* users[BT_L];

	BTreeDataNode(): stored(0), parent(NULL) {}
	~BTreeDataNode();
	void insert(User* user);
	void insert(User* user, int i);
	void print();
	bool canInsert() {return stored < BT_L;}
	BTreeDataNode split(User* user);
	int findUserI(User* user);
	int shiftUser(int i);
};

struct UserNode {
	AL_Head* AList;
	User user;

	~UserNode() {
		delete AList;
	}
};

class BTree {
public:
	BTreeNodePtr root;

	void insert(User* user);
};

#endif
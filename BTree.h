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


	BTreeNodePtr(): type(NONE) {}
	BTreeNodePtr(BTreePathNode* node) {
		type = PATH;
		path = node;
	}
	BTreeNodePtr(BTreeDataNode* node) {
		type = DATA;
		data = node;
	}

	void makeNewData();
	void makeNewPath();

	int getMin();

	void print();

	void del();
};

struct BTreePathNode {
	BTreePathNode* parent;
	int stored;
	int permKeys[BT_M-1];
	BTreeNodePtr children[BT_M];

	BTreePathNode(): stored(0) {}

	void insert(BTreeNodePtr node);
	void insert(BTreePathNode* node);
	void insert(BTreeNodePtr node, int i);
	int getNodeI(BTreeNodePtr node);
	int getUserI(User* user);
	void shiftNode(int i);

	int getMin();

	void print();
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
	BTreeDataNode* split(User* user);
	int findUserI(User* user);
	void shiftUser(int i);

	int getMin();
};

struct UserNode {
	AL_Head* AList;
	User user;

	UserNode(User& user): AList(nullptr), user(user) {}
};

class BTree {
public:
	BTreeNodePtr root;

	void insert(User* user);
	void insert(BTreeNodePtr node, User* user);
	void insert(BTreeNodePtr node, BTreeDataNode data);

	void print();
};

#endif
#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include "User.h"
#include "Graph.h"

struct BTreePathNode;
struct BTreeDataNode;
struct BTreeNodePtr;

struct BTreePathNode {
	int M;
	std::vector<int> perms;
	std::vector<BTreeNodePtr> children;
};

struct BTreeDataNode {
	int L;
	std::vector<User> users;
};

struct BTreeNodePtr {
	enum {PATH, DATA} type;
	union {
		BTreePathNode* path;
		BTreeDataNode* data;
	};
};

struct UserNode {
	AL_Head* AList;
	User user;
};

class BTree {
public:
	int M;
	int L;
	BTreeNodePtr root;
};

#endif
#ifndef BTREE_H
#define BTREE_H

// #include <vector>
#include "User.h"
#include "Graph.h"

struct BTree {
	static const int M = 4;
	static const int L = 2;

	struct Path;
	struct Data;
	struct Ptr;
	struct UserNode;

	struct UserNode {
		AL_Head* list;
		User* user;

		UserNode();
		UserNode(User* user, AL_Head* list);
		
		void del();
	};

	struct Ptr {
		enum {NONE, PATH, DATA} type;
		union {
			Path* path;
			Data* data;
		};

		Ptr();
		Ptr(Path* node);
		Ptr(Data* node);

		Ptr insert(UserNode user);
		UserNode getUser(int perm);
	        

		int getMin();
		void print(int tabH);
		void del();
	};

	struct Path {
		int stored;
		int keys[M-1];
		Ptr children[M];

		Path();
		~Path();

		int getFindI(int perm);
		int getInsertI(int perm);
		Ptr insert(UserNode user);
		Ptr insert(Ptr node);
		Ptr baseInsert(Ptr node, int i);
		Ptr splitInsert(Ptr node, int i);
		void shiftChildren(int i);

		UserNode getUser(int perm);

		int getMin();
		void print(int tabH);
	};

	struct Data {
		int stored;
		BTree::UserNode users[L];

		Data();
		~Data();

		int getUserI(UserNode user);
		Ptr insert(UserNode user);
		Ptr baseInsert(UserNode user, int i);
		Ptr splitInsert(UserNode user, int i);
		void shiftUsers(int i);

	  UserNode getUser(int perm);
	
		int getMin();
		void print(int tabH);
	};

	Ptr root;

	~BTree();

	void insert(User* user, AL_Head* list);
        User* getUser(int perm);
	AL_Head* getList(int perm);

	void print();
};

#endif

#ifndef BTREE_H
#define BTREE_H

// #include <vector>
#include "User.h"
#include "Graph.h"

class BTree {
public:
	static const int M = 4;
	static const int L = 2;

// private:
	struct Path;
	struct Data;
	struct Ptr;

	struct Ptr {
		enum {NONE, PATH, DATA} type;
		union {
			Path* path;
			Data* data;
		};

		Ptr();
		Ptr(Path* node);
		Ptr(Data* node);

		Ptr insert(User* user);

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
		Ptr insert(User* user);
		Ptr insert(Ptr node);
		Ptr baseInsert(Ptr node, int i);
		Ptr splitInsert(Ptr node, int i);
		void shiftChildren(int i);

		int getMin();
		void print(int tabH);
	};

	struct Data {
		int stored;
		User* users[L];

		Data();
		~Data();

		int getUserI(User* user);
		Ptr insert(User* user);
		Ptr baseInsert(User* user, int i);
		Ptr splitInsert(User* user, int i);
		void shiftUsers(int i);

		int getMin();
		void print(int tabH);
	};

// public:
	Ptr root;

	void insert(User* user);
	void print();
};

#endif
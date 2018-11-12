#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct AL_Head;
struct AL_Node;

struct AL_Head {
	int perm;
	AL_Node* head;

	~AL_Head();
};

struct AL_Node {
	int perm;
	AL_Node* next;

	~AL_Node();
};

class Graph {
public:
	std::vector<AL_Head> ALists;
};

#endif
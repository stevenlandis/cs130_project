#include "Graph.h"

AL_Head::~AL_Head() {
	if (head != NULL) delete head;
}

AL_Node::~AL_Node() {
	if (next != NULL) delete next;
}
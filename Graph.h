#ifndef GRAPH_H
#define GRAPH_H

#include <vector>


struct AL_Head;
struct AL_Node;

struct AL_Head {
	int perm = 0;
	AL_Node* head = NULL;

	~AL_Head();
};

struct AL_Node {
	int perm = 0;
	AL_Node* next = NULL;

	~AL_Node();
};

class Graph {
public:
	std::vector<AL_Head> ALists;

	AL_Head* addUser(int perm, std::vector<int> friends);
	void addFriendToUser(AL_Head* user, int friendPerm);
	bool isFriend(AL_Head* user, int friendPerm);
	std::vector<int> listFriends(AL_Head* user);
};

#endif

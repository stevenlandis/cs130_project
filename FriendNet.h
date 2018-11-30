#ifndef FRIEND_NET_H
#define FRIEND_NET_H

#include "BTree.h"
#include "User.h"
#include "Graph.h"
#include <string>
#include <vector>

class FriendNet {
 public:
  Graph graph;
  BTree tree;

  void readInputFile(std::string filepath);
  
  void addUser(
	       int perm_number,
	       std::string name,
	       std::string genre1,
	       std::string genre2,
	       std::vector<int> friends
	       );

  void findUser(int perm);

  void findUserDetails(int perm);

  void recommendFriends(int perm);
  
  void print();
};

#endif

#include "Graph.h"

#include <iostream>

AL_Head::~AL_Head() {
  std::cout << "Destructor\n";
  if (head != NULL){
    std::cout << "Head not null\n";
    delete head;
  }
  std::cout << "Destructor finished \n";
}

AL_Node::~AL_Node() {
	if (next != NULL) delete next;
}

//case that a new user is added, so new graph node
AL_Head* Graph::addUser(int perm, std::vector<int> friends){
  //create the head
  AL_Head* head = new AL_Head;
  head->perm = perm;
  if(friends.size() == 0){
    return head;
  }
  // add first friend
  int friendPerm = friends[0];
  AL_Node* new_node = new AL_Node;
  new_node->perm = friendPerm;
  head->head = new_node;
  AL_Node* node = new_node;
  // add rest of friends
  for(int i = 1; i < friends.size(); i++){
    friendPerm = friends[i];
    // add to user
    new_node = new AL_Node;
    new_node-> perm = friendPerm;
    node->next = new_node;
    node = node->next;
    // add to friend
  }
  return head;
}

//case that existing user is friended to a new user, old graph node
void Graph::addFriendToUser(AL_Head* user, int friendPerm){
  if(user == NULL){ // nice, user doesnt exist
    return;
  }
  AL_Node* new_node = new AL_Node;
  new_node->perm = friendPerm;
  AL_Node* node = user->head;
  if(node == NULL){
    user->head = new_node;
    return;
  }
  while(node->next != NULL){
    if(node->perm == friendPerm){ // friend already added
      delete new_node;
      return;
    }
    node = node->next;
  }
  if(node->perm == friendPerm){ // might also be the last node
    delete new_node;
    return;
  }
  node->next = new_node;
}

bool Graph::isFriend(AL_Head* user, int friendPerm){
  AL_Node* friendNode = user->head;
  while(friendNode != NULL){
    if(friendNode->perm = friendPerm)
      return true;
    friendNode = friendNode->next;
  }
  return false;
}


std::vector<int> Graph::listFriends(AL_Head* user){
  AL_Node* friendNode = user->head;
  std::vector<int> list;
  while(friendNode != NULL){
    list.push_back(friendNode->perm);
    friendNode = friendNode->next;
  }
  return list;
}

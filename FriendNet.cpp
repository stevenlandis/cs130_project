#include "FriendNet.h"
#include <fstream>
#include "iostream"
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;

void FriendNet::readInputFile(std::string filepath){
    std::string line;
    std::ifstream file;
    file.open(filepath);
    while(std::getline(file,line)){
        int perm = 0;
        std::string name, genre1, genre2;
        std::vector<int> friends;
        int i = 0;
        while(line[i] != ';'){
            perm *= 10;
            perm += line[i]-'0';
	    i++;
        }
        i++;
        while(line[i] != ';'){
            name += line[i];
            i++;
        }
        i++;
        while(line[i] != ';'){
            genre1 += line[i];
            i++;
        }
        i++;
        while(line[i] != ';'){
            genre2 += line[i];
            i++;
        }
        i++;
        while(i < line.length()){
            int companion = 0;
            while(i < line.length() && line[i] != ';'){
	      companion *= 10;
	      companion += line[i] - '0';
	      i++;
            }
            friends.push_back(companion);
            i++;
        }
	addUser(perm, name, genre1, genre2, friends);
    }
    
}
    
void FriendNet::findUser(int perm){
  User* u = tree.getUser(perm);
  if(u == NULL){
    cout << "User with perm, " << perm << ", not found.\n";
  }else{
    cout << "User with perm, " << perm << ", found.\n";
  }
}

void FriendNet::findUserDetails(int perm){
  User* u = tree.getUser(perm);
  if(u == NULL){
    cout << "User with perm, " << perm << ", not found.\n";
  }else{
    cout << "User name: " << u->name << endl;
    cout << "User favorite genre 1: " << u->genre1 << endl;
    cout << "User favorite genre 2: " << u->genre2 << endl;
    AL_Head* list = tree.getList(perm);
    std::vector<int> friends = graph.listFriends(list);
    if(friends.size() == 0){
      cout << "User does not have any friends." << endl;
    }else{
      cout << "User is friends with " << friends[0];
      for(int i = 1; i < friends.size(); i++){
	cout << ", " << friends[i];
      }
      cout << endl;
    }
  }
}

void FriendNet::recommendFriends(int perm){
  AL_Head* list = tree.getList(perm);
  if(list == NULL){
    cout << "User does not exist, cannot recommend friends :(\n";
    return;
  }
  std::vector<int> users = graph.listFriends(tree.getList(perm));
  std::unordered_map<int,int> depths;
  depths.insert({perm, 0});
  int directFriends = users.size();
  for(int i = 0; i < users.size(); i++){
    depths.insert({users[i], 1});
  }

  //start adding friends of friends..
  int index = 1;
  while(index < users.size()){
    int otherPerm = users[index];
    std::vector<int> otherFriends = graph.listFriends(tree.getList(otherPerm));
    int depth = depths[users[index]];
    for(int i = 0; i < otherFriends.size(); i++){
      if(depths.find(otherFriends[i]) == depths.end()){
	//not in list, add to back with depth + 1
	depths.insert({otherFriends[i], depth + 1});
	users.push_back(otherFriends[i]);
      }
    }
    index++;
  }

  //start searching through users
  //skip all direct friends and self
  bool userFound = false;
  User* user = tree.getUser(perm);
  std::string genre1 = user->genre1, genre2 = user->genre2;
  index = directFriends + 1;
  while(index < users.size()){
    User* user = tree.getUser(users[index]);
    if(genre1 == user->genre1 || genre1 == user->genre2 || genre2 == user->genre1 || genre2 == user->genre2){
      //recommend user
      cout << "Found recommended user with perm: " << user->perm_number <<endl
	   << "\tName: " << user->name <<endl
	   << "\tGenre1: " << user->genre1 <<endl
	   << "\tGenre2: " << user->genre2 << endl;
      //remember
      userFound = true;
    }
    index++;
  }

  if(!userFound){
    cout << "No recommendations found.\n";
  }
}
    

void FriendNet::addUser(
			int perm_number,
			std::string name,
			std::string genre1,
			std::string genre2,
			std::vector<int> friends
            ) {
  //check if user already exists
  User* user = tree.getUser(perm_number);
  if(user != NULL){
    //update name, genres
    user->name = name;
    user->genre1 = genre1;
    user->genre2 = genre2;
    //add friends
    AL_Head* list = tree.getList(perm_number);
    for(int i = 0; i < friends.size(); i++){
      graph.addFriendToUser(list, friends[i]);
      AL_Head* companion = tree.getList(friends[i]);
      if(companion != NULL){
	graph.addFriendToUser(companion, perm_number);
      }
    }
    return;
  }
  
  // make a new user
  User* newUser = new User(perm_number, name, genre1, genre2);
  
  // add the user to the friend net
  AL_Head* newHead = graph.addUser(perm_number, friends);
  
  //add new user as a friend to its friends
  for(int i = 0; i < friends.size(); i++){
    AL_Head* companion = tree.getList(friends[i]);
    if(companion != NULL){
      graph.addFriendToUser(companion, perm_number);
    }
  }
  
  
  // tree owns and deletes newUser
  tree.insert(newUser, newHead);
}

void FriendNet::print() {
    tree.print();
    cout << endl;
}

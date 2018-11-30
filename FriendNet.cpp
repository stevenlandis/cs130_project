#include "FriendNet.h"
#include <fstream>
#include "iostream"

using std::cout;
using std::endl;

void FriendNet::readInputFile(std::string filepath){
    std::string line;
    std::ifstream file;
    file.open(filepath);
    while(std::getline(file,line)){
        int perm;
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
            int companion;
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

}

void FriendNet::findUserDetails(int perm){

}

void FriendNet::recommendFriends(int perm){

}
    

void FriendNet::addUser(
            int perm_number,
            std::string name,
            std::string genre1,
            std::string genre2,
            std::vector<int> friends
            ) {
    // make a new user
    User* newUser = new User(perm_number, name, genre1, genre2);

    // add the user to the friend net
    AL_Head* newHead = graph.addUser(perm_number, friends);
    
    // tree owns and deletes newUser
    tree.insert(newUser, newHead);
}

void FriendNet::print() {
    tree.print();
    cout << endl;
}
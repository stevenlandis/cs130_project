#include <iostream>
#include "FriendNet.h"
#include <vector>
#include <string>

using namespace std;

int getIntValueFromInput(){
  std::string value = "";
  int amount = 0;
  while(true){
    std::cin >> value;
    try{
      amount = std::stoi(value);
      if(amount >= 0){
	return amount;
      }
    }catch(std::invalid_argument e){}
    std::cout << "Value " << value << " is invalid. Please enter a positive integer.\n";
  }
}

std::string getGenreFromInput(){
  std::string choice = "";
  std::cout << "Enter one of the following genres:\n"
	    << "1: Action\n"
	    << "2: Adventure\n"
	    << "3: Comedy\n"
	    << "4: Crime\n"
	    << "5: Drama\n"
	    << "6: Fantasy\n"
	    << "7: Horror\n"
	    << "8: Sci-Fi\n";
  while(true){
    std::cin >> choice;
    if(choice == "1" || choice == "Action"){
      return "Action";
    }else if(choice == "1" || choice == "Action"){
      return "Action";
    }else if(choice == "2" || choice == "Adventure"){
      return "Adventure";
    }else if(choice == "3" || choice == "Comedy"){
      return "Comedy";
    }else if(choice == "4" || choice == "Crime"){
      return "Crime";
    }else if(choice == "5" || choice == "Drama"){
      return "Drama";
    }else if(choice == "6" || choice == "Fantasy"){
      return "Fantasy";
    }else if(choice == "7" || choice == "Horror"){
      return "Horror";
    }else if(choice == "8" || choice == "Sci-Fi"){
      return "Sci-Fi";
    }else{
      std::cout << "Choice " << choice << " is invalid. Please enter a valid genre.\n"; 
    }
  }
}

int main() {
  cout << "Welcome to the friend recommender\n";
  FriendNet friendNet;
  std::string choice = "";

  while(choice != "q"){
    std::cout << "Please choose one of the following operations:\n"
	      << "1: Read from input file\n"
	      << "2: Add user manually\n"
	      << "3: Find a user\n"
	      << "4: Find a user's details\n"
	      << "5: Recommend friends to a user\n"
	      << "q: Exit the program\n";
    std::cin >> choice;
    if(choice == "1"){
      std::cout << "Reading from input file..\n";
      friendNet.readInputFile("users_friendship.txt");
      std::cout << "Finished reading..\n";
    }else if(choice == "2"){
      std::cout << "Please enter a perm number:\n";
      int perm = getIntValueFromInput();
      std::cout << "Please enter a name:\n";
      std::string name;
      std::cin >> name;
      std::cout << "Please enter a genre:\n";
      std::string genre1 = getGenreFromInput();
      std::cout << "Please enter a second genre:\n";
      std::string genre2 = getGenreFromInput();
      vector<int> friends;
      std::cout << "Please enter friends of this user using their perm one at a time\n";
      std::cout << "When finished, enter 'done'\n";
      std::string companion; // friend is a keyword :/ 
      while(true){
	std::cin >> companion;
	try{
	  int fperm = std::stoi(companion);
	  friends.push_back(fperm);
	  std::cout << "Added friend with perm " << fperm << ".\n";
	}catch(std::invalid_argument e){
	  break;
	}
      }
      friendNet.addUser(perm, name, genre1, genre2, friends);
      std::cout << "User has been added\n";
    }else if(choice == "3"){
      std::cout << "Enter a perm number to be searched for:\n";
      int perm = getIntValueFromInput();
      std::cout << "Searching for user...\n";
      friendNet.findUser(perm);
      std::cout << "Done searching...\n";
    }else if(choice == "4"){
      std::cout << "Enter a perm number to be searched for:\n";
      int perm = getIntValueFromInput();
      std::cout << "Searching for user details...\n";
      friendNet.findUserDetails(perm);
      std::cout << "Done searching...\n";
    }else if(choice == "5"){
      std::cout << "Enter a perm number to be recommended for:\n";
      int perm = getIntValueFromInput();
      std::cout << "Recommending friends for user...\n";
      friendNet.recommendFriends(perm);
      std::cout << "Done searching...\n";
    }else if(choice == "q"){
      std::cout << "Goodbye..\n";
    }else{
      std::cout << "You entered: " + choice + " which is not an option.";
    }
  }
  /*
  vector<int> friends = {1,2,3,4,5};
  friendNet.addUser(1003, "John", "stuff", "things", friends);
  friendNet.addUser(1002, "John", "stuff", "things", friends);
  friendNet.addUser(1001, "John", "stuff", "things", friends);
  
  friendNet.print();
  
  friendNet.addUser(1000, "John", "stuff", "things", friends);
  */
}

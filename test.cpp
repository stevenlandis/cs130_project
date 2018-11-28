#include <iostream>
#include "FriendNet.h"
#include <vector>
#include <string>

using namespace std;

int main() {
  cout << "Starting\n";

  FriendNet friendNet;
  
  vector<int> friends = {1,2,3,4,5};
  friendNet.addUser(5, "John", "stuff", "things", friends);
  friendNet.addUser(3, "John", "stuff", "things", friends);
  friendNet.addUser(1, "John", "stuff", "things", friends);
  
  friendNet.print();
  
  friendNet.addUser(0, "John", "stuff", "things", friends);
  
}

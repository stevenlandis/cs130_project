#include <iostream>
#include "FriendNet.h"
#include <vector>
#include <string>

using namespace std;

int main() {
  cout << "Starting\n";

  FriendNet friendNet;
  // friendNet.print();
  
  vector<int> friends = {1,2,3,4,5};
  friendNet.addUser(5, "John", "stuff", "things", friends);
  friendNet.addUser(3, "John", "stuff", "things", friends);

  // friendNet.print();

  friendNet.addUser(1, "John", "stuff", "things", friends);
  friendNet.addUser(7, "John", "stuff", "things", friends);
  friendNet.addUser(9, "John", "stuff", "things", friends);
  friendNet.addUser(110, "John", "stuff", "things", friends);
  friendNet.addUser(130, "John", "stuff", "things", friends);
  
  // friendNet.print();

  friendNet.addUser(150, "John", "stuff", "things", friends);
  friendNet.addUser(170, "John", "stuff", "things", friends);
  friendNet.addUser(8, "John", "stuff", "things", friends);
  friendNet.addUser(10, "John", "stuff", "things", friends);
  friendNet.addUser(11, "John", "stuff", "things", friends);
  friendNet.addUser(12, "John", "stuff", "things", friends);
  friendNet.addUser(13, "John", "stuff", "things", friends);
  friendNet.addUser(14, "John", "stuff", "things", friends);
  friendNet.addUser(15, "John", "stuff", "things", friends);
  friendNet.addUser(6, "John", "stuff", "things", friends);
  friendNet.addUser(4, "John", "stuff", "things", friends);

  friendNet.print();

  cout << "Search for list 13 --> " << friendNet.tree.getList(13) << endl;
  
  // friendNet.addUser(0, "John", "stuff", "things", friends);
  
}

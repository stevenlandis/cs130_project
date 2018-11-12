#include <iostream>
#include "FriendNet.h"
#include <vector>

using namespace std;

int main() {
	cout << "Starting\n";

	FriendNet friendNet;

	vector<int> friends = {1,2,3,4,5};
	friendNet.addUser(1001, "John", "stuff", "things", friends);
	friendNet.addUser(1002, "John", "stuff", "things", friends);
	// friendNet.addUser(1003, "John", "stuff", "things", friends);
}
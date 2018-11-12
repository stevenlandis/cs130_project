#include "FriendNet.h"

void FriendNet::addUser(
		int perm_number,
		std::string name,
		std::string genre1,
		std::string genre2,
		std::vector<int> friends
) {
	// make a new user
	User* newUser = new User(perm_number, name, genre1, genre2);

	tree.insert(newUser);
}
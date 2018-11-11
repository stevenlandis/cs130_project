#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
	int perm_number;
	std::string name;
	std::string genre1;
	std::string genre2;

	User(int perm_number, std::string name, std::string genre1, std::string genre2);
private:
};

#endif
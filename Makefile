all: exec
	./exec

exec: main.cpp FriendNet.h FriendNet.cpp BTree.cpp BTree.h User.cpp User.h Graph.cpp Graph.h
	g++ -g -std=c++11 -o exec main.cpp FriendNet.cpp BTree.cpp User.cpp Graph.cpp

clean:
	rm -f exec
	rm -rf exev.dSYM
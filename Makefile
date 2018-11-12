all: exec
	./exec

exec: main.cpp FriendNet.h FriendNet.cpp BTree.cpp BTree.h User.cpp User.h Graph.cpp Graph.h
	g++ -g -o exec main.cpp FriendNet.cpp BTree.cpp User.cpp Graph.cpp

clean:
	rm exec
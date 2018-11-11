all: exec
	./exec

exec: main.cpp BTree.cpp BTree.h User.cpp User.h Graph.cpp Graph.h
	g++ -o exec main.cpp BTree.cpp User.cpp Graph.cpp
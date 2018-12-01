CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

HEADERS = FriendNet.h BTree.h User.h Graph.h
CPPFILES = FriendNet.cpp BTree.cpp User.cpp Graph.cpp

main: mainExec
	./mainExec

test: testExec
	./testExec

testLeaks: testExec
	valgrind --leak-check=yes ./testExec

mainExec: $(HEADERS) $(CPPFILES) main.cpp
	g++ -g -std=c++11 -o mainExec main.cpp $(CPPFILES)

testExec: $(HEADERS) $(CPPFILES) test.cpp
	g++ -g -std=c++11 -o testExec test.cpp $(CPPFILES)

clean:
	rm -f mainExec testExec
	rm -rf mainExec.dSYM

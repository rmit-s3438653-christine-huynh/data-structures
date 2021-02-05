OBJS = main.o c_list.o c_bst.o my_vector.o my_set.o
CC = g++
CXXFLAGS = -Wall -pedantic -std=c++14
RM = rm -f
all : a1

a1: main.o c_list.o c_bst.o my_vector.o my_set.o
	$(CC) main.o c_list.o c_bst.o my_vector.o my_set.o -o a1 -lboost_program_options -L/usr/lib64 -lstdc++

main.o : main.cpp c_list.h c_bst.h my_vector.h my_set.h
	$(CC) $(CXXFLAGS) -c main.cpp

c_list.o : c_list.cpp c_list.h
	$(CC) $(CXXFLAGS) -c c_list.cpp

c_bst.o : c_bst.cpp c_bst.h
	$(CC) $(CXXFLAGS) -c c_bst.cpp

my_vector.o : my_vector.cpp my_vector.h
	$(CC) $(CXXFLAGS) -c my_vector.cpp

my_set.o : my_set.cpp my_set.h
	$(CC) $(CXXFLAGS) -c my_set.cpp

#my_list.o : my_list.cpp my_list.h
#	$(CC) $(CXXFLAGS) -c my_list.cpp

clean:
	$(RM) $(OBJS)

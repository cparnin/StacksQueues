
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
CFLAGS  = $(INCLUDE_DIR)
CCFLAGS = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIB_LIST    = -lm
LIBS = $(LIB_PATH) $(LIB_LIST)

objects = ListNode.o List.o ListIterator.o general.o Stack.o Queue.o canfield.o main.o

default: canfield

canfield: $(objects)
	g++ -g -o canfield $(objects)

ListNode.o : ListNode.cc ListNode.h
	g++ -c ListNode.cc -o ListNode.o

ListIterator.o : ListIterator.cc ListIterator.h ListNode.h
	g++ -c ListIterator.cc -o ListIterator.o

List.o : List.cc List.h ListNode.h general.h
	g++ -c List.cc -o List.o

canfield.o : canfield.cc canfield.h Stack.h Queue.h
	g++ -c canfield.cc -o canfield.o

Stack.o : Stack.cc Stack.h List.h
	g++ -c Stack.cc -o Stack.o

Queue.o : Queue.cc Queue.h List.h
	g++ -c Queue.cc -o Queue.o

general.o : general.cc general.h
	g++ -c general.cc -o general.o

main.o : main.cc canfield.h
	g++ -c main.cc -o main.o


clean :
	rm *.o
	rm canfield

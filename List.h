/*********************************************************************
  Authors:       Chad Parnin & Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     List.h
  Last updated:  September 4, 2014.
  Description:   Definition of a container class for a list. Using the
                 list iterator for browsing.
**********************************************************************/

#ifndef LIST_H
#define LIST_H

#include "ListNode.h"
#include "ListIterator.h"

class List {

private:
    ListNodePtr head, tail;
    int size;

public:
    // Default constructor.
    List();

    // Copy constructor. The target object should be assigned a hard
    // copy of the list contained in the data object.
    List(const List &data);

    // Destructor.
    ~List();

    // Assignment operator. It must also make a hard copy of the
    // list. Make sure that the tail of the target object is also set
    // correctly.
    List &operator=(const List &data);

    // Returns the size of the list.
    int getSize();

    // Inserts a new node with the specified content at the front of the
    // list. It must make sure to update both the head and the tail of
    // the list if need be.
    void insertFront(int number=0);

    // Removes the node in the list after the one pointed to by the
    // current in the iterator. If the iterator contains a NULL pointer,
    // it removes the front node. It returns false if the list was empty
    // and no node was removed.
    bool removeNodeAfter(ListIterator iter);
    
    // Checks if the list is empty.
    bool isEmpty();

    // Converts to boolean. It must return true if the list is not empty,
    // and false if it is. 
    operator bool();

    // Deletes the entire list and resets all the data.
    void makeEmpty();

    // Prints the list. We also want to know how many node are there in
    // the list and if the list is empty.
    void print();

    // Checks if the list is in ascending order.
    bool isOrdered();

    // Concatenates the second list to the first and empties the second
    // list.
    void concatenate(List &data);

    // Difference operator - it must compare the content of the two
    // lists and not just the pointers to them.
    bool operator!=(const List &data);

    // Prints the last node in the list: the tail.
    void printLast();

    // Functions using the list iterator

    // Begining of the list returned as a list iterator.
    ListIterator begin();
    // End of the list returned as a list iterator.
    ListIterator end();

    // Finds the given number in the list and return a list iterator
    // containing a pointer to the node containing the number in
    // question. If the number is not in the list, it returns an iterator 
    // where the pointer current is NULL.
    ListIterator locate(int number);

    // The bubble sort using list iterators.
    void bubbleSort();


    // Functions to be written by the student.

    // Comparison operator - it must compare the content of the two
    // lists and not just the pointers to them.
    bool operator==(const List &data);

    // Inserts a new node with the specified content at the back of the
    // list. Could be calling another class method if appropriate. The
    // code must be supplied by the student.
    void insertBack(int number=0);

    // Counts the number of negative values in the list. If the list is
    // empty, just return 0.
    int countNegative();  

    // A useful function. This one does not need a list iterator

    // Removes the front node from the list and delete the memory for the
    // node to be removed. The function should return true if the list
    // is not empty, and false if the list is already empty. The head
    // and the tail (!) of the list should be updated correctly.
    bool removeFront();

    // Inserts a node after the node pointed to by current in the
    // iterator. We assume that the existing node is part of the list. If
    // current in the iterator is NULL, then the function should insert
    // the new node at the front of the list. The function should update
    // head, tail, and size properly.
    void insertAfter(ListIterator iter, int number);

    // This function computes the sum of all the numbers stored in the
    // list. It should be implemented using list iterators.
    int sum();

    // This function prints the sum of the first list
    void printSum(int sumOf);

    // Returns the element i of the list in the form of a list iterator,
    // where i=0 returns the first node of the list. If the list has
    // less than i+1 nodes, then it should return a null iterator.
    ListIterator nodeAtPosition(int location);

    // Print the datum at position x specified by user
    // It takes a List Iterator pointing to node and returns datum
    void printPositionX();
    
    // Locates a number (datum) specified by user
    // It takes the user's number from printNodeLocation function
    // It returns the location as a simple integer
    int locateNumber(int number);
    
    // Prints the node location of the data the user specifies
    void printNodeLocation();
    
    // This function should implement the selection sort on a list using
    // list iterators. It should have an iterator scanning the list but
    // stopping before the last node. For every position in the list, it
    // would have to find the location of the minimal number in the list
    // using a call to the appropriate function from the
    // list_iterator. Then if the location of the minimum is not the
    // same as the current node, swap the value of the current node with
    // the minimum.
    void selectionSort();
    
    // Very simple display of the List with no other messages.
    void display();

}; // class List



#endif

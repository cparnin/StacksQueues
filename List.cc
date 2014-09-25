/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     List.cc
  Last updated:  September 4, 2014
  Description:   Implementation of a container class for a list.

**********************************************************************/

#include <iostream>
using namespace std;
#include "general.h"
#include "List.h"
#include <iomanip>

// Default constructor.
List::List()
    : head(NULL), tail(NULL), size(0) // empty list
{
} // List::List()

// Copy constructor. The target object should be assigned a hard copy
// of the list contained in the data object.
List::List(const List &data)
    : head(NULL), tail(NULL), size(0) // start with an empty list
{
    *this = data; // then use the operator= form this class
} // List::List()

// Destructor.
List::~List()
{
    // call the function makeEmpty instead so that we only have to
    // change things in one place
    makeEmpty();
} // List::~List()

// Assignment operator. It must also make a hard copy of the
// list. Make sure that the tail of the target object is also set
// correctly.
List &List::operator=(const List &data)
{
    if (this != &data) // check that we're not assigning the object to itself
    {
        size = data.size;
        head = data.head->copy(); // make a copy of the list instead of 
                                  // of assigning just the pointer 
        tail = head->lastNode();  // now we have to find the last node
                                  // because we've copied the list
    }

    return *this; 
} // List::operator=()

// Returns the size of the list.
int List::getSize()
{
    return size;
} // List::getSize()

// Inserts a new node with the specified content at the front of the
// list. It must make sure to update both the head and the tail of the
// list if need be.
void List::insertFront(int number)
{
    // create a node with the data and pointing towards the head
    ListNodePtr newNode = new ListNode(number, head);
    testAllocation(newNode);

    size++; // we're adding a node

    head = newNode; // this one becomes the head of the list

    if (size == 1)      // if it was the first one
        tail = newNode; // then it's also the tail
} // List::insertFront()

// Removes the node in the list after the one pointed to by the
// current in the iterator. If the iterator contains a NULL pointer,
// it removes the front node. It returns false if the list was empty
// and no node was removed.
bool List::removeNodeAfter(ListIterator iter)
{
    if (!iter) // current in iter is NULL
        return removeFront();
    else 
    {
        if (!iter.current->next) // iter is the last node
            return false; // nothing to remove in this case
        else
        {
            ListNodePtr temp = iter.current->next; // the node to delete
            iter.current->next = iter.current->next->next; // adjust links
            delete temp;
            size--;
            if (!iter.current->next) // if the node we deleted was the last one
                tail = iter.current; // then we have a new tail.
            return true;
        }
    }
} // List::removeNodeAfter()

// Checks if the list is empty.
bool List::isEmpty()
{
    return (size == 0); // we can check the size or the pointers
} // List::isEmpty()

// Converts to boolean. It must return true if the list is not empty,
// and false if it is.
List::operator bool()
{
    return !isEmpty(); // return true if the list is not empty
} // List::operator bool()

// Deletes the entire list and reset all the data.
void List::makeEmpty()
{
    if (size) // if the list is not empty
    {
        deleteList(head); // call the function from ListNode.cc
        head = NULL; // then reset the data
        tail = NULL;
        size = 0;
    }
} // List::makeEmpty()

// Difference operator - it must compare the content of the two lists
// and not just the pointers to them.
bool List::operator!=(const List &data)
{
    return !(*this == data); // call the operator== on the object,
                             // not on the pointer
} // List::operator!=()

// Concatenates the second list to the first and empties the second
// list.
void List::concatenate(List &data)
{
    if (head != data.head) // if the two lists are not the same
    {
        if (head) // if the first list is not empty
        {
            // call the ListNode function to add the second list 
            // to the tail of the first
            tail->concatenate(data.head); 
            size += data.size; // we also have to update the size
            if (data.tail)     // and the tail
                tail = data.tail;
        }
        else // if the first list is empty
        {
            // move the list from the second one into it
            head = data.head;
            size = data.size;
            tail = data.tail;
        }
        if (data) // if the second list was not empty, unlink/empty it
        {
            data.size = 0;
            data.head=NULL;
            data.tail=NULL;
        }
    }
    else // error
        cout << "Attepmt to concatenate a list to itself. "
             << "Operation ignored." << endl;
} // List::concatenate()
  
// Prints the last node in the list: the tail.
void List::printLast()
{
    if (tail) // check that we have a last node
        cout << "The last node in the list contains " 
             << tail->datum << endl;
    else
        cout << "The list is empty, it has no last node" << endl;
} // List::printLast()

/*******************************************************************/
// Functions using list iterators.

// Begining of the list returned as a list iterator.
ListIterator List::begin()
{
    return ListIterator(head); 
} // 

// End of the list returned as a list iterator.
ListIterator List::end()
{
    return ListIterator(tail);
} // List::end()

// Prints the list. We also want to know how many node are there in
// the list and if the list is empty.  I have rewriten this function
// using list iterators.
void List::print()
{
    // print the count first
    cout << "The list has " << size << " nodes." << endl;

    if (size)   // if the list is not empty
    {
        // print all the nodes using an iterator
        cout << "Here are the nodes of the list:" << endl;
        ListIterator iter(head); //start from the head
        while (iter) // while we haven't reached the end
        {
            cout << *iter << ' '; // print the datum
            ++iter; // move to the next node
        }
        cout << endl;
    }
} // List::print()

// Finds the given number in the list and return a list iterator
// containing a pointer to the node containing the number in
// question. If the number is not in the list, it returns an iterator   
// where the pointer current is NULL.
ListIterator List::locate(int number)
{
    ListIterator locator = begin(); // start form the head
    while (locator && *locator != number) // while we haven't reached the end
                                          // nor found the target
        ++locator; // move to the next node
    return locator; // return the iterator containing the target
                    // or containing NULL if it wasn't there
} // List::locate()

// The bubble sort using list iterators.
void List::bubbleSort()
{
    if (head) // if the list is not empty
    {
        bool ordered = false;
        ListIterator iter1, iter2; // need two iterators
        while (!ordered) // while the list is not sorted
        {
            ordered = true; // we'll assume it is sorted
            iter1 = head;   // start form the head with one
            iter2 = head->next; // and the next with the other
            while (iter2) 
            {
                if (*iter1 > *iter2) // if two nodes are out of order
                {
                    iter1.swap(iter2); // swap their datums
                    ordered = false;   // and set the flag
                }
                ++iter1; // move both iterators at the same time
                ++iter2; // so they will allways be adjacent nodes
            }
        }
    }
} // List::bubbleSort()

/*******************************************************************/
// Functions to be written by the student. 


// Comparison operator - it must compare the content of the two
// lists and not just the pointers to them.
bool List::operator==(const List &data)
{
    if (size != data.size) // if they're not the same size, they're not equal
        return false;
    ListIterator listOne = head; // create 2 iterators
    ListIterator listTwo = data.head;
    while (listOne.current != NULL)
    {
        if (*listOne != *listTwo) // compare datum
            return false;
        else
        {
            ++listOne; // iterate to next
            ++listTwo;
        }
    }
    return true; // they are the same
} // List::operator==()


// Inserts a new node with the specified content at the back of the
// list. Could be calling another class method if appropriate.
void List::insertBack(int number)
{
    insertAfter(end(), number); // delegate to insertAfter with an iterator
                                // containing a pointer to the last node
} // List::insertBack()

// Inserts a node after the node pointed to by current in the
// iterator. We assume that the existing node is part of the list. If
// current in the iterator is NULL, then the function should insert
// the new node at the front of the list. The function should update
// head, tail, and size properly.
void List::insertAfter(ListIterator iter, int number)
{
    if (!iter) // if the iterator contains NULL
        insertFront(number);
    else
    {
        ListNodePtr newNode = new ListNode(number); // create a new node
        testAllocation(newNode);
        newNode->next = iter.current->next; // link the one after iter to it
        iter.current->next = newNode; // link iter to it
        size++;
        if (iter.current == tail)
            tail = newNode;
    }
} // List::insertAfter()


// Checks if the list is in ascending order.
bool List::isOrdered()
{
    ListIterator temp1 = head;
    ListIterator temp2 = head;
    if (!temp1) // if NULL
        return true; // stop
    ++temp2; // go to next node to prepare for comparing
    if (!temp2) // if no second node, it's in order
        return true;
    while (temp2) // until NULL
    {
        if (*temp1 > *temp2) // compare datum
            return false;
        ++temp1;
        ++temp2;
    }
    return true;
} // List::isOrdered()

// Counts the number of negative values in the list. If the list is
// empty, just return 0.
int List::countNegative()
{
    int neg = 0; // negative number tally
    ListIterator temp = head; // start from beginning
    if (!temp) // if NULL
        return 0; // stop
    while (temp) // while not NULL
    {
        if (*temp < 0) // if negative datum
            ++neg; 
        ++temp; // iterate
    }
    return neg; // return number of negative numbers
} // List::countNegative()

// Removes the front node from the list and delete the memory for the
// node to be removed. The function should return true if the list is
// not empty, and false if the list is already empty. The head and the
// tail (!) of the list should be updated correctly.  THIS DOES NOT
// NEED TO USE ITERATORS.
bool List::removeFront()
{
    if (!head) // if the list is empty then there is nothing
    return false; // to delete
    ListNodePtr temp = head;
    head = head->next;
    delete temp;
    --size;
    if (!head) // we deleted the last node
        tail = NULL;
    return true; // Return true if we deleted a node
} // List::removeFront()

// This function computes the sum of all the numbers stored in the
// list. It should be implemented using list iterators.
int List::sum()
{
    ListIterator temp = head; // create iterator to tally
    int sum = 0;
    if (!head)
        return 0; // leave if no nodes
    else
    {
        while (temp) // until NULL
        {
            sum += *temp; // dereference temp to extract datum
            temp = ++temp;
        }
    }
    return sum;    // Returns sum for printSum function
} // List::sum()

// This function prints the sum of the first list and takes
// the sum of the sum() function
void List::printSum(int sumOf)
{
    cout << "\nThe sum of the first list is:\n";
    cout << sumOf << endl;
} // List::printSum()

// Returns the element i of the list in the form of a list iterator,
// where i=0 returns the first node of the list. If the list has less
// than i+1 nodes, then it should return a null iterator. Use the
// function move_forward from the class ListIterator.
ListIterator List::nodeAtPosition(int location)
{
    // This is what the function will return if location is 0. 
    ListIterator start = begin();
    if ((location > size) || (location <= 0))
        // not enough nodes or not at least position 1
        return NULL;
    else
        start.moveForward(location); // start stepping
    return start; // return pointer to that node
} // List::nodeAtPosition()

// Returns the element i of the list in the form of a list iterator,
// where i=0 returns the first node of the list. If the list has less
// than i+1 nodes, then it should return a null iterator. Use the
// function move_forward from the class ListIterator.
void List::printPositionX()
{
    int location = 0;
    cout << "Enter the node to find: ";
    cin >> location;
    cout << location << endl;
    ListIterator x = nodeAtPosition(location); // find that node
    cout << "The node contains the value of -> ";
    cout << *x << endl; // extract datum
} // List::printPositionX(ListIterator x)

//
int List::locateNumber(int number)
{
    int step = 1; // create node counter
    ListIterator temp = head; // create Iterator to traverse
    while (temp) // while temp not NULL
    {
        if (*temp != number) // compare datum
        {
            ++temp; // increment
            step += step; // increment
        }
        else
            break; // if found, break loop
    }
    if (!temp) // if we never found it
    {
        cout << "\nCouldn't find node with given data\n";
        return 0;
    }
    return step; // return the node position
} // List::locateNumber(int number)

void List::printNodeLocation()
{
    int num = 0;
    cout << "Which number would you like to locate? ";
    cin >> num;
    int x = locateNumber(num); // call to find location
    if (x != 0) // if found it
    {
        cout << "The node with the given data is at location ";
        cout << x << endl;
    }
    else // if it didn't find it
        return;
} // List::printNodeLocation()

// This function should implement the selection sort on a list using
// list iterators.It should have an iterator scanning the list but
// stopping before the last node. For every position in the list, it
// would have to find the location of the minimal number in the list
// using a call to the appropriate function from the
// list_iterator. Then if the location of the minimum is not the same
// as the current node, swap the value of the current node with the
// minimum.
void List::selectionSort()
{
    if (head) // if the list is not empty
    {
        ListIterator iter1, iter2; // need two iterators
        iter1 = head;
        iter2 = head;
        ++iter2;
        while(iter2)
        {
            iter2 = iter1.min();
            if (*iter2 < *iter1)
                iter2.swap(iter1);
            ++iter1;
            iter2 = iter1;
        }
    }
} // List::selectionSort()

// Very simple display of the List with no other messages.
void List::display()
{
    if (size)
    {
        ListIterator iter(head);
        while (iter)
        {
            cout << setw(2) << *iter << ' ';
            ++iter;
        }
    }

} // List::display()
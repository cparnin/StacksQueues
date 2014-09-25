
/*********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     Queue.cc
  Last updated:  September 2014
  Description:   Implementation of a class queue derived from a list.
**********************************************************************/

#include <iostream>
#include <cstdlib>
using namespace std;

#include "Queue.h"

// Default constructor: create an empty stack.
Queue::Queue() : List()
{
} //Queue::Queue()

// Insert an object into the stack.
void Queue::enqueue(int data)
{
    insertBack(data); // CHANGED FROM insertFront(data)
} // Queue::enqueue()

// Remove the top object and return its value.
int Queue::dequeue()
{
    int result = front();  // CHANGED FROM top()
    removeFront();
    return result;
} // Queue::dequeue()

// Inspect the value of the top object.
int Queue::front()
{ 
    if (!isEmpty()) 
        return *begin();
    else 
    {
        cout << "attempting to access the front element of an empty queue" << endl;
        exit(1);
    }  
} // Queue::front()

// Delete all the objects in the stack.
void Queue::makeEmpty()
{ 
    List::makeEmpty(); 
}// Queue::makeEmpty()

// Test if the stack is empty.
bool Queue::isEmpty()
{ 
    // return !(List)(*this); 
    return List::isEmpty();
} // Queue::isEmpty()

// Concatenate two stacks.
void Queue::concatenate(Queue &other)
{
    List::concatenate(other);
} // Queue::concatenate()

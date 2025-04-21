#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Customer.h"
#include <iostream>

struct Node {
  Customer data;
  Node *nextPtr;
  Node(Customer data, Node *nextPtr);
};

class LinkedList {
private:
  Node *headPtr; // Points to first node in the list
  int count;     // Number of nodes in the list

public:
  LinkedList();
  ~LinkedList(); // Added destructor to clean up memory
  void add(Customer item);
  Customer &peek()
      const; // return the contents of the front of the list (but do not remove)
  void delElement(); // remove a node item from the front of the list
  void printList() const;
  bool listIsEmpty() const; // return true if the list is empty (headPtr =
                            // nullptr?), false otherwise
  int size() const;
};

#endif // LINKEDLIST_H

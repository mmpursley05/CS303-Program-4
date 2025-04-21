#include "LinkedList.h"
#include <stdexcept>
using namespace std;

// Sivkan:
// Use initializer list to initialize Customer data members
Node::Node(const Customer data, Node *nextPtr) : data(data), nextPtr(nextPtr) {}

LinkedList::LinkedList() {
  headPtr = nullptr;
  count = 0;
}

LinkedList::~LinkedList() {
  // Clear all nodes to prevent memory leaks
  Node *current = headPtr;
  while (current != nullptr) {
    Node *next = current->nextPtr;
    delete current;
    current = next;
  }
  headPtr = nullptr;
  count = 0;
}

// Sivkan:
// Add customer to linked list, sorted by checkout readiness time
void LinkedList::add(Customer item) {
  Node *newNode = new Node(item, nullptr);
  // Case 1: List is empty or new node goes at the head
  if (headPtr == nullptr || item.enterAQTime < headPtr->data.enterAQTime) {
    newNode->nextPtr = headPtr;
    headPtr = newNode;
    count++;
    return;
  }
  // Case 2: Insert somewhere after head
  Node *current = headPtr;
  while (current->nextPtr != nullptr &&
         current->nextPtr->data.enterAQTime <= item.enterAQTime) {
    current = current->nextPtr;
  }
  // Insert the new node
  newNode->nextPtr = current->nextPtr;
  current->nextPtr = newNode;
  count++;
}

// Return the first customer in the list without removing them
Customer &LinkedList::peek() const {
  if (count == 0 || headPtr == nullptr) {
    throw std::invalid_argument("Cannot peek. List is empty.\n");
  }
  return headPtr->data;
}

// Remove the first customer from the list
void LinkedList::delElement() {
  if (count == 0 || headPtr == nullptr) {
    throw std::invalid_argument("Cannot delete. List is empty.\n");
  }
  Node *temp = headPtr;
  headPtr = headPtr->nextPtr;
  delete temp;
  count--;
}

// Print all customers in the shopping list for debugging
void LinkedList::printList() const {
  Node *current = headPtr;
  std::cout << "Shopping List: ";
  if (current == nullptr) {
    std::cout << "Empty";
  }
  while (current != nullptr) {
    std::cout << "[ID:" << current->data.cartId
              << ", Items:" << current->data.itemCount
              << ", ReadyAt:" << current->data.enterAQTime << "] ";
    current = current->nextPtr;
  }
  cout << endl;
}

bool LinkedList::listIsEmpty() const { return (headPtr == nullptr); }
int LinkedList::size() const { return count; }

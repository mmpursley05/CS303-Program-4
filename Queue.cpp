#include "Queue.h"
#include <iostream>

// Maggie:
QueueNode::QueueNode(Customer data, QueueNode *nextPtr)
    : data(data), nextPtr(nextPtr) {}

Queue::Queue() {
  front = nullptr;
  rear = nullptr;
}

Queue::~Queue() {
  // Clear all nodes when queue is destroyed
  while (front != nullptr) {
    QueueNode *temp = front;
    front = front->nextPtr;
    delete temp;
  }
  rear = nullptr;
}

// Maggie:
// Add customer to checkout queue and update statistics
void Queue::enQueue(Customer item) {
  QueueNode *node = new QueueNode(item, nullptr);
  if (front == nullptr) {
    front = node;
    rear = node;
  } else {
    rear->nextPtr = node;
    rear = node;
  }
  qData.queueCount++;
  if (qData.queueCount > qData.maxQueueLength) {
    qData.maxQueueLength = qData.queueCount;
  }
  qData.currentItems += item.itemCount;
  qData.totalItems += item.itemCount;
}

// Maggie: Remove customer from checkout queue and update statistics
Customer Queue::deQueue() {
  if (qData.queueCount == 0 || front == nullptr) {
    throw std::invalid_argument("Cannot deQueue. Queue is empty.\n");
  }
  QueueNode *temp = front;
  Customer tempData = temp->data;
  front = front->nextPtr;
  if (front == nullptr) {
    rear = nullptr;
  }
  delete temp;
  qData.queueCount--;
  qData.currentItems -= tempData.itemCount;
  qData.customersServed++; // Increment customers served
  qData.cartsServed.push_back(tempData);
  return tempData;
}

Customer &Queue::peek() const {
  if (qData.queueCount == 0 || front == nullptr) {
    throw std::invalid_argument("Cannot peek. Queue is empty.\n");
  }
  return front->data;
}

bool Queue::queueEmpty() const { return (front == nullptr); }

void Queue::printQueue() const {
  QueueNode *current = front;
  std::cout << "Queue: ";
  while (current != nullptr) {
    std::cout << "[ID:" << current->data.cartId
              << ", Items:" << current->data.itemCount << "] ";
    current = current->nextPtr;
  }
  std::cout << std::endl;
}

// Maggie:
// Calculate total items in checkout queue
int Queue::getTotalItemsWaiting() const {
  int total = 0;
  QueueNode *current = front;
  while (current != nullptr) {
    total += current->data.itemCount;
    current = current->nextPtr;
  }
  return total;
}

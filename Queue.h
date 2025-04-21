#ifndef QUEUE_H
#define QUEUE_H
#include "Customer.h"
#include <stdexcept>
#include <vector>

// Maggie:
struct QueueNode {
  Customer data;
  QueueNode *nextPtr;

  QueueNode(Customer data, QueueNode *nextPtr);
};

struct queueData {
  int queueCount = 0;    // current queue length (set to 0 initially)
  int totalIdleTime = 0; // if queueCount == 0; this is incremented
  int totalOverTime =
      0; // increment if current time > 720 & there are people in line
  int maxQueueLength = 0;  // if current queueCount>maxQueueLength, reset
  int currentItems = 0;    // update as customers are added/removed from queue
  int totalItems = 0;      // running count of items purchased
  int customersServed = 0; // number of customers processed through this queue

  std::vector<Customer> cartsServed;
};

class Queue {
private:
  QueueNode *front; // Points to first node in the queue
  QueueNode *rear;  // Points to last node in the queue

public:
  queueData qData; // Statistics for this queue
  Queue();
  ~Queue();                    // Added destructor to clean up memory
  void enQueue(Customer item); // add the customer item to the end of the queue
  Customer deQueue();      // remove a customer item from the front of the queue
  Customer &peek() const;  // return the contents of the front of the queue (but
                           // do not remove)
  bool queueEmpty() const; // return true if the queue is empty (front =
                           // nullptr?), false otherwise
  void printQueue() const; // print the queue contents
  int getTotalItemsWaiting() const;
};

#endif // QUEUE_H

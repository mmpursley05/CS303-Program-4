#include "Customer.h"
#include "Functions.h"
#include "LinkedList.h"
#include "Queue.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Katy:
// Function to print statistics for all checkout lines
void printStatistics(const vector<Queue> &queues) {
  for (int i = 0; i < queues.size(); i++) {
    cout << "CHECKOUT LINE: " << (i + 1) << endl;
    cout << "       Total Customers Helped:  " << setw(5)
         << queues[i].qData.customersServed << endl;
    cout << "       Total Number of Items:   " << setw(5)
         << queues[i].qData.totalItems << endl;
    cout << "       Max Line Length:         " << setw(5)
         << queues[i].qData.maxQueueLength << endl;
    cout << "       Total Idle Time:         " << setw(5)
         << queues[i].qData.totalIdleTime << endl;
    cout << "       Total Over Time:         " << setw(5)
         << queues[i].qData.totalOverTime << endl;
    cout << endl;
  }
}

// Maggie:
// Function to determine which checkout queue has the fewest items waiting
int findShortestQueue(const vector<Queue> &queues) {
  int shortestQueueIndex = 0;
  int minTotalItems = queues[0].getTotalItemsWaiting();

  // Iterate through all queues to find the one with the least items
  for (int j = 1; j < queues.size(); j++) {
    int itemsInThisQueue = queues[j].getTotalItemsWaiting();
    if (itemsInThisQueue < minTotalItems) {
      minTotalItems = itemsInThisQueue;
      shortestQueueIndex = j;
    }
  }
  return shortestQueueIndex;
}

int main() {
  // Katy:
  // Initialize random seed
  srand(static_cast<unsigned int>(time(nullptr)));

  // Display welcome message and program introduction
  cout << "Grocery Store Simulation\n";
  cout << "=======================\n\n";

  // Sivkan:
  // Initialize the linked list for tracking shopping customers
  LinkedList list;

  // Katy:
  // Get user input for number of checkout lines and validate
  int checkoutLines;
  cout << "Enter number of checkout lines (1-10): ";
  cin >> checkoutLines;
  while (checkoutLines < 1 || checkoutLines > 10) {
    cout << "Please enter number of checkout lines between 1 and 10: ";
    cin >> checkoutLines;
  }

  // Maggie:
  // Initialize the vector of checkout queues based on user input
  vector<Queue> customersQueue(checkoutLines);

  // Sivkan:
  // Initialize customer ID counter and simulation time
  int id = 0;
  int currentTime = 0;

  // Katy:
  // Simulation start notification
  cout << "\nStore is now open. Simulation starting...\n\n";

  // Main simulation loop for store open hours (12 hours = 720 minutes)
  for (currentTime = 0; currentTime <= 720; currentTime++) {
    // Sivkan:
    // Determine how many customers arrive this minute (1-3)
    int customersArriving = (rand() % 3) + 1;

    // Count current total customers in all queues
    int totalInQueues = 0;
    for (const auto &queue : customersQueue) {
      totalInQueues += queue.qData.queueCount;
    }

    // Limit new arrivals if store is getting too crowded (more than 50 in
    // queues)
    if (totalInQueues > 50) {
      customersArriving = 1;
    }

    // Create new customers who arrive at the store
    for (int j = 0; j < customersArriving; j++) {
      int items =
          getItemsPurchased(); // Random number of items based on distribution
      int totalShoppingTime =
          ceil(getTotalShoppingTime(items)); // Calculate shopping time
      id++;                                  // Increment unique customer ID
      // Create customer with ID, item count, and time they'll be ready for
      // checkout
      Customer customer(id, items, currentTime + totalShoppingTime);
      list.add(customer); // Add customer to shopping list
    }

    // Maggie:
    // Move customers from shopping to checkout when they're ready
    while (!list.listIsEmpty() && list.peek().enterAQTime == currentTime) {
      Customer customer = list.peek();
      list.delElement(); // Remove from shopping list
      // Find the queue with the fewest items
      int shortestQueueIndex = findShortestQueue(customersQueue);
      // Calculate when customer will be done with checkout
      customer.checkoutTime = getCheckoutTime(customer, currentTime);
      // Add customer to shortest checkout queue
      customersQueue[shortestQueueIndex].enQueue(customer);
    }

    // Process checkouts and update queue statistics
    for (auto &queue : customersQueue) {
      // Remove customers who are done with checkout
      if (!queue.queueEmpty() && queue.peek().checkoutTime <= currentTime) {
        queue.deQueue();
      }
      // Katy:
      // Update idle time if queue is empty during store hours
      if (queue.queueEmpty() && currentTime <= 720) {
        queue.qData.totalIdleTime++;
      }
    }

    // Katy:
    // Status update every hour (60 minutes)
    if (currentTime % 60 == 0 && currentTime > 0) {
      cout << "Time: " << setw(3) << currentTime << " minutes - ";
      cout << "Customers shopping: " << setw(3) << list.size() << ", ";

      int totalInQueues = 0;
      for (const auto &queue : customersQueue) {
        totalInQueues += queue.qData.queueCount;
      }
      cout << "Customers in checkout: " << setw(3) << totalInQueues << endl;
    }
  }

  // Katy:
  // Store closing notification
  cout << "\nStore is now closed at " << 720
       << " minutes. Processing remaining customers...\n";

  // Track remaining customers for simulation end condition checks
  int remainingShoppers = list.size();
  int remainingInCheckout = 0;
  for (const auto &queue : customersQueue) {
    remainingInCheckout += queue.qData.queueCount;
  }
  cout << "Remaining shoppers: " << remainingShoppers
       << ", Remaining in checkout: " << remainingInCheckout << endl;

  // Set maximum overtime limit (2 hours)
  const int MAX_OVERTIME = 120;

  // Overtime processing loop until all customers are served or max overtime
  // reached
  while ((!list.listIsEmpty() || !areShoppingLanesEmpty(customersQueue)) &&
         (currentTime - 720) < MAX_OVERTIME) {
    currentTime++;

    // Maggie:
    // Continue processing customers who finish shopping during overtime
    while (!list.listIsEmpty() && list.peek().enterAQTime <= currentTime) {
      Customer customer = list.peek();
      list.delElement(); // Remove from shopping list
      int shortestQueueIndex = findShortestQueue(customersQueue);
      customer.checkoutTime = getCheckoutTime(customer, currentTime);
      customersQueue[shortestQueueIndex].enQueue(customer);
    }

    // Process customers in checkout queues
    for (auto &queue : customersQueue) {
      if (!queue.queueEmpty() && queue.peek().checkoutTime <= currentTime) {
        queue.deQueue();
      }

      // Katy:
      // Update overtime statistics for occupied queues after store closing
      if (currentTime > 720 && !queue.queueEmpty()) {
        queue.qData.totalOverTime++;
      }
    }

    // Katy:
    // Report overtime status every 15 minutes
    if (currentTime > 720 && (currentTime - 720) % 15 == 0) {
      cout << "Overtime: " << setw(3) << (currentTime - 720) << " minutes - ";
      cout << "Customers still shopping: " << setw(3) << list.size() << ", ";

      int totalInQueues = 0;
      for (const auto &queue : customersQueue) {
        totalInQueues += queue.qData.queueCount;
      }
      cout << "Customers in checkout: " << setw(3) << totalInQueues << endl;

      // Check for stalled simulation (no progress after 60 minutes of overtime)
      if ((currentTime - 720) > 60 && totalInQueues == remainingInCheckout &&
          list.size() == remainingShoppers) {
        cout << "No progress after 60 minutes of overtime. Ending simulation."
             << endl;
        break;
      }

      // Update tracking variables for next progress check
      remainingShoppers = list.size();
      remainingInCheckout = totalInQueues;
    }
  }

  // Handle maximum overtime condition
  if ((currentTime - 720) >= MAX_OVERTIME) {
    cout << "Maximum overtime reached. Ending simulation." << endl;
  }

  // Print final simulation statistics
  cout << "\n\nFinal Statistics:\n";
  cout << "================\n";
  printStatistics(customersQueue);

  // Calculate overall statistics
  int totalCustomers = 0;
  int totalItems = 0;
  int totalIdleTime = 0;
  int totalOverTime = 0;

  for (const auto &queue : customersQueue) {
    totalCustomers += queue.qData.customersServed;
    totalItems += queue.qData.totalItems;
    totalIdleTime += queue.qData.totalIdleTime;
    totalOverTime += queue.qData.totalOverTime;
  }

  // Katy:
  // Display overall statistics
  cout << "Overall Statistics:\n";
  cout << "Total Customers Served: " << totalCustomers << endl;
  cout << "Total Items Processed: " << totalItems << endl;
  cout << "Average Items Per Customer: " << fixed << setprecision(2)
       << (totalCustomers > 0 ? static_cast<double>(totalItems) / totalCustomers
                              : 0)
       << endl;
  cout << "Average Idle Time Per Lane: " << fixed << setprecision(2)
       << (checkoutLines > 0
               ? static_cast<double>(totalIdleTime) / checkoutLines
               : 0)
       << endl;
  cout << "Average Overtime Per Lane: " << fixed << setprecision(2)
       << (checkoutLines > 0
               ? static_cast<double>(totalOverTime) / checkoutLines
               : 0)
       << endl;

  return 0;
}

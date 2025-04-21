#include "Functions.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

// Sivkan:
int getItemsPurchased() {
  int r = rand() % 100; // Generate a number from 0 to 99

  // Distribution according to assignment requirements:
  // 45% purchase fewer than 10 items
  if (r < 45) {
    return (rand() % 10) + 1; // 1-10 items
  }
  // 30% purchase 11-20 items
  else if (r < 75) {
    return (rand() % 10) + 11; // 11-20 items
  }
  // 15% purchase 21-30 items
  else if (r < 90) {
    return (rand() % 10) + 21; // 21-30 items
  }
  // 10% purchase 31-60 items
  else {
    return (rand() % 30) + 31; // 31-60 items
  }
}

// Sivkan:
// calculate shopping time per item
double getTimePerItem() {
  // Random time between 30-60 seconds (0.5-1.0 minutes)
  return ((rand() % 31) + 30) / 60.0;
}

// Sivkan:
// Calculate total shopping time based on number of items
double getTotalShoppingTime(int numItems) {
  double total = 0;
  for (int i = 0; i < numItems; i++) {
    total += getTimePerItem();
  }
  return total;
}

// Katy: Helper function to check if all shopping lanes are empty
bool areShoppingLanesEmpty(const std::vector<Queue> &shoppingLanes) {
  for (const auto &lane : shoppingLanes) {
    if (!lane.queueEmpty()) {
      return false;
    }
  }
  return true;
}

// Maggie:
// Calculate checkout time for a customer
int getCheckoutTime(Customer &customer, int currentTime) {
  // Each item takes 0.05 minutes to checkout (instead of 0.15)
  // Use ceiling to round up to nearest minute
  int checkoutDuration = std::ceil(customer.itemCount * 0.15);
  // Ensure minimum checkout time is 1 minute
  if (checkoutDuration < 1)
    checkoutDuration = 1;
  return currentTime + checkoutDuration;
}

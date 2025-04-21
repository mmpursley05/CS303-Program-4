#include "Customer.h"

// Sivkan:
// Customer class implementation
Customer::Customer(int cartId, int itemCount, int enterAQTime) {
  this->cartId = cartId;
  this->itemCount = itemCount;
  this->enterAQTime = enterAQTime;
  this->checkoutTime = -1; // Initialize to -1, will be set later
}

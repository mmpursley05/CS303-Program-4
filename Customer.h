#ifndef CUSTOMER_H
#define CUSTOMER_H

// Sivkan:
// Customer class definition
struct Customer {
  int cartId;      // unique id assigned for each cart
  int itemCount;   // amount of items the customer will get (randomly generated)
  int enterAQTime; // current ‘time’ + shopping time
  int checkoutTime = -1;
  Customer(int cartId, int itemCount, int enterAQTime);
};

#endif // CUSTOMER_H

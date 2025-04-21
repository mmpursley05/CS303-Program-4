#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Queue.h"
#include <vector>

int getItemsPurchased();
double getTimePerItem();
double getTotalShoppingTime(int numItems);
bool areShoppingLanesEmpty(const std::vector<Queue> &shoppingLanes);
int getCheckoutTime(Customer &customer, int time);
#endif // FUNCTIONS_H

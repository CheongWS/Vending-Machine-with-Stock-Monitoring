#ifndef PAYMENT_hpp
#define PAYMENT_hpp

#include <iostream>    // Access library.
#include "product.hpp" // Header file.

using namespace std;

void total_price (Product product, int quantity);   
void calc_change (double price, double money);
bool process_payment (Product product, int quantity, double money);
void saveSales(Product product, int quantity);
#endif

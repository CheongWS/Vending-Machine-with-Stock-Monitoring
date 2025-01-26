#ifndef VENDINGMACHINE_hpp
#define VENDINGMACHINE_hpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "product.hpp"
#include "payment.hpp"
#include "staff.hpp"

using namespace std;

class vendingMachine {
private:
    vector<Product> products;

public:
    vendingMachine(); // Constructor.

    void displayProducts(); // Displaying the products in the vending machine.

    void selectProduct(string choice, int quantity, double money); // Selecting the product from the vending machine.

    bool checkStock(Product product, int quantity); // Checking the availability of the product in the vending machine.

    void enterQuantity(int& quantity); // Entering quantity of the product.

    void enterMoney(double& money); // Entering the money.

    void updateStock(Product product, int quantity); // Monitoring the stock of the vending machine.

    void saveInventory(); // Saving the inventory of the vending machine.

    void loadInventory(); // Loading the inventory of the vending machine.

    void initial(vector<Product>& products); // Function declaration without qualification.

    void updateVectorFromMap(std::vector<Product>& products, const std::map<std::string, int>& stock,const std::map<std::string, double>& prices);

    void populateStockMap();

    void populatePriceMap();
};

#endif
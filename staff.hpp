#ifndef STAFF_HPP
#define STAFF_HPP

#include <iostream>           // To perform input and output operations.
#include <iomanip>            // To assign precise decimal places and formatting stock display.
#include <string>             // Provides std::string class.
#include <map>                // To store data in mapped method. 
#include <limits>             // Defines various properties and limitations of fundamental numeric types. 
#include <fstream>            // To perform input and output operations on files.
#include <sstream>            // To perform input and output operations on string-based streams.
#include <algorithm>          // To perform a range of elements in a container.

using namespace std;

// Inventory data structures //
extern map<string, int> stock;     // Stores item names and their quantities.
extern map<string, double> prices; // Stores item names and their prices.


// Function declarations //
// Save the updated inventory to a file //
void saveInventoryToFile(const string& filename);

// Save the inventory to the maps //
bool staffLogin();       

// Manage the items in the inventory //
void manageItems();       

// Set or readjust the price of an item //
void setItemPrices();     

// Display the stock of the vending machine //
void displayStock();      

//display the sales of the vending machine
void displaySales();

// Display the staff menu //
void staffMenu();         

// Prevent processing failure of the program if the inputs are alphabets while integers are expected //
void safeInput(int& value, const string& prompt, int minValue = numeric_limits<int>::min(), int maxValue = numeric_limits<int>::max());

// Display the products in the vending machine //
void saveInventorytoMap(const string& filename); 

#endif 

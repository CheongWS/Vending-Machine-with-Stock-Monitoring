// Programmers name (entire .cpp): CHEONG WYE SHEN
// Matrix ID                     : 23302183
// Purpose                       : This .cpp file is to define the functions for the staff to manage and monitor the stock of the vending machine.

#include "staff.hpp"          // Header file.
#include "vendingMachine.hpp" // Header file.
#include "product.hpp"        // Header file.
#include <iostream>           // To perform input and output operations.
#include <iomanip>            // To assign precise decimal places and formatting stock display.
#include <string>             // Provides std::string class.
#include <map>                // To store data in mapped method. 
#include <limits>             // Defines various properties and limitations of fundamental numeric types. 
#include <fstream>            // To perform input and output operations on files.
#include <sstream>            // To perform input and output operations on string-based streams.
#include <algorithm>          // To perform a range of elements in a container.

using namespace std;

// Definitions for inventory data //
map<string, int> stock;
map<string, double> prices;

// Function to save the updated inventory to a file //
void saveInventoryToFile(const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cout << "Error opening file for saving inventory.\n";
        return;
    }

    for (const auto& [item, quantity] : stock) {
        outputFile << item << "|" << prices[item] << "|" << quantity << "\n";
    }

    outputFile.close();
    cout << "Inventory saved to " << filename << ".\n";
}

void saveInventorytoMap(const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "Error opening file.\n";
        return;
    } 

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, priceStr, quantityStr;
        double price;
        int quantity;

        // Parse the line using '|' as a delimiter //
        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, quantityStr, '|');

        // Convert price and quantity to their respective types //
        price = stod(priceStr);
        quantity = stoi(quantityStr);

        // Insert into the maps //
        prices[name] = price;
        stock[name] = quantity;
    }

    inputFile.close();
}

// Login credentials //
const string STAFF_USERNAME = "Admin";
const string STAFF_PASSWORD = "17698";

bool staffLogin() {
    string username, password;
    int attempts = 3; // Allows up to 3 attempts before redirecting to main menu to prevent endless loops.

    while (attempts > 0) {
        cout << "\nStaff Login\n";
        // Input username from staff //
        cout << "Please enter your Username > ";
        // Clear any leftover input buffer if needed (e.g., after previous use of cin >>).
        if (cin.peek() == '\n') {
            cin.ignore(); // Consume the leftover newline character.
        }
        getline(cin, username); 
        if (username.empty()) { // Check for empty input.
            cout << "Username cannot be empty.\n";
            continue;
        }

        // Input password from staff //
        cout << "Please enter your Password > ";
        getline(cin, password); 
        if (password.empty()) { 
            cout << "Password cannot be empty.\n";
            continue;
        }

        // Check credentials validity //
        if (username == STAFF_USERNAME && password == STAFF_PASSWORD) {
            cout << "Login successful! Welcome, Admin.\n";
            return true; // Successfully logged in as the input for username and password is correct.
        } else {
            attempts--;
            cout << "Invalid password or username. You have " << attempts << " attempt(s) remaining.\n"; // Wrong username or password.
        }
    }
    cout << "Too many failed attempts. Redirecting to main menu.\n";
    vendingMachine vm;
    vm.displayProducts(); // Display the products in the vending machine.
    return false; // Failure to log in after exhausting attempts.
}

// This function is the menu for staff to choose his or her actions //
void staffMenu() {
    saveInventorytoMap("inventory.txt");
    
    string choice;
    while (true) {
        cout << "\nStaff Menu:\n";
        cout << "==========================\n";
        cout << "Please select an option:\n";
        cout << "1. Restock or Remove Items\n";
        cout << "2. Set Item Prices\n";
        cout << "3. View Stock\n";
        cout << "4. View Sales\n";
        cout << "5. Exit to Main Menu\n";
        cout << "==========================\n";
        
        cout << "Enter your choice (1 - 5) > ";
        cin >> choice;

        // Switch case with string for choice handling //
        if (choice == "1") {
            manageItems();
        } else if (choice == "2") {
            setItemPrices();
        } else if (choice == "3") {
            displayStock();
        } else if (choice == "4") {
            displaySales();
        } else if (choice == "5") {
            cout << "Returning to main menu.\n";
            return;
        } else {
            cout << "Invalid choice. Please try again by entering input within the given range.\n";
        }
    }
}

// This function works to restock or remove items from the inventory //
void manageItems() {
    string item;
    string choice;
    int quantity;

    cout << "\nInventory Management\n";
    cout << "======================\n";
    cout << "1. Restock items\n";
    cout << "2. Remove expired items\n";
    cout << "Enter 0 to return to staff menu.\n";
    cout << "Enter your choice (1-2) > ";
    cin >> choice;

    // Switch case with string for choice handling //
    while (choice != "0" && choice != "1" && choice != "2") {
        cout << "Invalid choice. Please try again by entering input within the given range.\n";
        cout << "Enter your choice (1-2) > ";
        cin >> choice;
        if (choice == "0") {
            cout << "Returning to staff menu...\n";
            staffMenu();
            return;
        }
    }

    if (choice == "1") {
        displayStock();
        cout << "\nEnter the item name > ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, item);

        if (stock.find(item) == stock.end()) {
            cout << "Item not found in inventory.\n";
            return;
        }

        safeInput(quantity, "Enter the amount of quantity to add (minimum requirement = 1) > ", 1);  // Set minimum to 1
        
        stock[item] += quantity;
        cout << "Successfully restocked " << item << " with " << quantity << " units.\n";
        cout << "New total stock: " << stock[item] << " units.\n";
        saveInventoryToFile("inventory.txt");
    }
    else if (choice == "2") {
        displayStock();
        cout << "\nEnter the item name > ";
        cin.clear(); // Clear off the fail state buffers.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To discard invalid input.
        getline(cin, item);

        if (stock.find(item) == stock.end()) {  // Check if the item is not in the inventory.
            cout << "Item not found in inventory.\n";
            return;
        }
        
        safeInput(quantity, "Enter the amount of quantity to remove (minimum requirement = 1) > ");
        while (quantity <= 0) {
            cout << "Error: Quantity must be greater than 0. Please try again.\n";
            safeInput(quantity, "Enter the amount of quantity to remove (minimum requirement = 1) > ");
        }

        if (stock[item] < quantity) {
            cout << "Error: Cannot remove more than the available stock.\n";
            return;
        }

        stock[item] -= quantity;
        cout << "Successfully removed " << quantity << " units of " << item << ".\n";
        cout << "New total stock: " << stock[item] << " units.\n";
        saveInventoryToFile("inventory.txt");
    }
}

// Set or readjust the price of an item //
void setItemPrices() {
    string item;
    string priceInput;
    double price;

    displayStock();
    while(true) {
        cout << "\n------------------Price Adjustment--------------------\n";
        cout << "Enter 0 to return to staff menu.\n";
        cout << "\nEnter the item name to update price > ";
            
            if (cin.peek() == '\n') {
            cin.ignore(); // Consume the leftover newline character.
        }
        
        // Remove redundant clear/ignore //
        getline(cin, item);

        // Trim whitespace from input //
        item.erase(0, item.find_first_not_of(" \t\n\r\f\v"));
        item.erase(item.find_last_not_of(" \t\n\r\f\v") + 1);

        if (item.empty()) {
            cout << "Item name cannot be empty.\n";
            continue;
        }

        if (item == "0") {
            cout << "Returning to staff menu...\n";
            return;
        }

        if (prices.find(item) == prices.end()) {
            cout << "Item not found in inventory.\n";
            continue;
        }

        while(true) {
            cout << "Enter the new price for " << item << " > ";
            cin >> priceInput;

            // Check if input contains only digits, decimal point, or negative sign
            bool isValid = true;
            int decimalPoints = 0;
            
            for(size_t i = 0; i < priceInput.length(); i++) {
                if (i == 0 && priceInput[i] == '-') continue;
                if (priceInput[i] == '.') {
                    decimalPoints++;
                    continue;
                }
                if (!isdigit(priceInput[i])) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid || decimalPoints > 1) {
                cout << "Invalid input! Please enter a valid price (e.g., 1.50).\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            try {
                price = stod(priceInput);
                
                if (price < 0) {
                    cout << "Price cannot be negative.\n";
                    continue;
                }
                if (price == 0) {
                    cout << "Price cannot be zero.\n";
                    continue;
                }

                prices[item] = price;
                cout << "Updated price of " << item << " to RM " << fixed << setprecision(2) << price << ".\n";
                saveInventoryToFile("inventory.txt");
                return;

            } catch (const invalid_argument&) {
                cout << "Invalid price format.\n";
                continue;
            }
        }
    }
}

// Display the current stock and prices //
void displayStock() {
    if (stock.empty()) {
        cout << "\nInventory is empty.\n";
        return; // To prevent displaying nothingness in the case where there's literally no stocks left.
    }

    cout << "\nCurrent Inventory:\n";
    cout << left 
         << setw(18) << "Item"
         << setw(13) << "Quantity"
         << setw(10) << "Price" << "\n";
    cout << string(40, '-') << "\n";

    for (const auto& [item, quantity] : stock) {
        cout << left 
             << setw(20) << item
             << setw(11) << quantity
             << "RM" << fixed << setprecision(2) << prices[item] << "\n";
    }
}

// Display the sales of the vending machine //
void displaySales() {
    ifstream inputFile("sales.txt");
    if (!inputFile) {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    double totalSales = 0.0;
    cout << "\nSales Report:\n";
    cout << left 
         << setw(20) << "Item"
         << setw(10) << "Price"
         << setw(10) << "Quantity"
         << setw(10) << "Total" << "\n";
    cout << string(50, '-') << "\n";

    while (getline(inputFile, line)) { // Read each line from the file.
        stringstream ss(line);
        string name, priceStr, quantityStr, totalStr;
        double price, total;
        int quantity;

        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, quantityStr, '|');
        getline(ss, totalStr, '|');

        price = stod(priceStr);
        quantity = stoi(quantityStr);
        total = stod(totalStr);

        cout << left 
             << setw(20) << name
             << "RM" << fixed << setprecision(2) << setw(8) << price
             << setw(10) << quantity
             << "RM" << fixed << setprecision(2) << setw(10) << total << "\n";

        totalSales += total; // Calculate the total sales.
    }

    cout << string(50, '-') << "\n";
    cout << "Total Sales: RM" << fixed << setprecision(2) << totalSales << "\n";
    inputFile.close();
}

// To prevent processing failure of the program if the inputs are alphabets while integers are expected //
void safeInput(int& value, const string& prompt, int minValue, int maxValue) {
    while (true) {
        cout << prompt;
        string input;
        cin >> input;
        
        // Remove whitespace //
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        
        // Check if input is empty //
        if (input.empty()) {
            cout << "Input cannot be empty.\n";
            continue;
        }

        // Check for decimal points (prevent error) //
        if (input.find('.') != string::npos) {
            cout << "Please enter a whole number.\n";
            continue;
        }

        // Check for any negative numbers. //
        bool isNegative = input[0] == '-';
        if (isNegative && minValue >= 0) {
            cout << "Negative numbers are not allowed.\n";
            continue;
        }

        try {
            value = stoi(input);
            if (value >= minValue && value <= maxValue) {
                break;
            }
            cout << "Please enter a number between " << minValue << " and " << maxValue << ".\n";
        }
        catch (const exception&) {
            cout << "Invalid input. Please enter a valid number.\n";
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}